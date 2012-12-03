#include <uC++.h>
#include "q1printer.h"
#include "q1bank.h"
#include "q1watcardoffice.h"
#include "MPRNG.h"
#include <iostream>

/********* main ************
 * Purpose: courier's actions, queues up for a job unless being told to
 *          call destructor
 * Returns: void
 * Arguments: none
 ***************************/
void WATCardOffice::Courier::main() {
  while (true) {
    _Accept(~Courier) {
      break;
    } else {
      // goes to get work from watcard office
      Job *task = office->requestWork();
      if (task->args.type == Destroy) {
        delete task;
        break;
      }
      unsigned int sid = task->args.sid;
      unsigned int amount = task->args.amount;
      WATCard *card = NULL;

      printer.print(Printer::Courier, id, 't', sid, amount);
      if (task->args.type == Create) {
          card = new WATCard();
          bank.withdraw(sid, 5);
          card->deposit(5);
      } else if (task->args.type == Transfer) {
          bank.withdraw(sid, amount);
          task->args.card->deposit(amount);
      }

      int fail = rng(5);
      // Simulate lost card
      if (fail == 0) {
        // delete the card
        if (task->args.card != NULL)
          delete task->args.card;
        if (card != NULL)
          delete card;
        // throw exception
        task->result.exception( new Lost );
      } else {
        if (task->args.card != NULL) {
          task->result.delivery(task->args.card);
        } else if (card != NULL) {
          task->result.delivery(card);
        }
        printer.print(Printer::Courier, id, 'T', sid, amount);
      }
      delete task;
    }
  }
}

/******** Courier **********
 * Purpose: courier constructor
 * Returns: Courier
 * Arguments: &bank - reference bank
 *            &prt - reference to printer
 *            *office - pointer to watcardoffice
 *            cid - courier id
 ***************************/
WATCardOffice::Courier::Courier(Bank &bank, Printer &prt, WATCardOffice *office, unsigned int cid) :
bank(bank), printer(prt){
  this->office = office;
  id = cid;
  printer.print(Printer::Courier, id, 'S');
}

/******** ~Courier *********
 * Purpose: courier destructor
 * Returns: void
 * Arguments: none
 ***************************/
WATCardOffice::Courier::~Courier(){
  printer.print(Printer::Courier, id, 'F');
}

/***** WATCardOffice ********
 * Purpose: WATCardOffice constructor
 * Returns: WATCardOffice
 * Arguments: &prt - reference to printer
 *            &bank - reference to bank
 *            numCouriers - number of couriers
 ***************************/
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), bank(bank) {
  this->numCouriers = numCouriers;
  couriers = new Courier* [numCouriers];
  for (unsigned int i = 0; i < numCouriers; i++)
    couriers[i] = new Courier(bank, prt, this, i);

  printer.print(Printer::WATCardOffice, 'S');
}

/***** ~WATCardOffice *******
 * Purpose: WATCardOffice destructor
 * Returns: none
 * Arguments: none
 ***************************/
WATCardOffice::~WATCardOffice() {
  for (unsigned int i = 0; i < numCouriers; i++)
    delete couriers[i];
  delete couriers;
  printer.print(Printer::WATCardOffice, 'F');
}

/********* main ************
 * Purpose: WATCardOffice main, accepts all functions
 * Returns: none
 * Arguments: none
 ***************************/
void WATCardOffice::main() {
  while (true) {
    _Accept(~WATCardOffice) {
      // Destory couriers by create a job with type=destroy when terminating office
      Args args = {Destroy, 0, 0, NULL};
      while(!jobCond.empty()) {
        Job *task = new Job(args);

        jobQueue.push_back(task);
        jobCond.signal();
      }
      break;
    } or _Accept(create) {
    } or _Accept(transfer) {
    } or _Accept(requestWork) {
    }
  }
}

/********* create **********
 * Purpose: creates a watcard for a student, with set amount
 * Returns: FTWATCard
 * Arguments: sid - student id
 *            amount - amount to be added to watcard
 ***************************/
FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  // Create job with arguments to create a watcard
  Args args = {Create, sid, amount, NULL};
  Job *task = new Job(args);
  // Add job to queue, signal any waiting couriers
  jobQueue.push_back(task);
  if(!jobCond.empty())
    jobCond.signal();
  printer.print(Printer::WATCardOffice, 'C', sid, amount);
  return task->result;
}

/********* transfer *********
 * Purpose: transfer money to a watcard for a student
 * Returns: FTWATCard
 * Arguments: sid - student id
 *            amount - amount to be added to watcard
 *            *card - pointer to student's watcard
 ***************************/
FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
  Args args = {Transfer, sid, amount, card};
  Job *task = new Job(args);
  jobQueue.push_back(task);
  if (!jobCond.empty())
    jobCond.signal();
  printer.print(Printer::WATCardOffice, 'T', sid, amount);
  return task->result;
}

/******* requestWork ********
 * Purpose: queues up couriers to wait for jobs
 * Returns: Job*
 * Arguments: none
 ***************************/
WATCardOffice::Job* WATCardOffice::requestWork(){
  if (jobQueue.empty())
    jobCond.wait();
  Job* task = jobQueue[0];
  if (task->args.type != Destroy)
    printer.print(Printer::WATCardOffice, 'W');
  jobQueue.erase(jobQueue.begin());
  return task;
}
