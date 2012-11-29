#include <uC++.h>
#include "q1printer.h"
#include "q1bank.h"
#include "q1watcardoffice.h"

void WATCardOffice::Courier::main() {
  while(true) {
    _Accept(~Courier) {
      break;
    } else {
      // Doesn't work yet, delete next two lines later
      Job *task = office->requestWork();
      //Args testArgs = {Transfer, 0, 10, new WATCard()};
      //Job *task = new Job(testArgs);

      unsigned int sid = task->args.sid;
      unsigned int amount = task->args.amount;

      // TODO: Simulate lost card
      printer.print(Printer::Courier, id, 't', sid, amount);
      if (task->args.type == Create) {            // This syntax is pretty ugly
          //printf("creating new watcard\n");
          task->args.card = new WATCard();
          task->args.card->deposit(5);
      } else if (task->args.type == Transfer) {
          bank.withdraw(sid, amount);             // Block here until funds are available
          task->args.card->deposit(amount);
      }
      printer.print(Printer::Courier, id, 'T', sid, amount);
    }
  }
}

WATCardOffice::Courier::Courier(Bank &bank, Printer &prt, WATCardOffice *office, unsigned int cid) :
bank(bank), printer(prt){
  this->office = office;
  id = cid;
  printer.print(Printer::Courier, id, 'S');
}

WATCardOffice::Courier::~Courier(){
  printer.print(Printer::Courier, id, 'F');
}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), bank(bank) {
  this->numCouriers = numCouriers;
  couriers = new Courier* [numCouriers];
  for (unsigned int i = 0; i < numCouriers; i++)
    couriers[i] = new Courier(bank, prt, this, i);

  printer.print(Printer::WATCardOffice, 'S');
}

WATCardOffice::~WATCardOffice() {
  for (unsigned int i = 0; i < numCouriers; i++)
    delete couriers[i];
  delete couriers;
  printer.print(Printer::WATCardOffice, 'F');
}

void WATCardOffice::main() {
  //while (true) {
    // _Accept(~WATCardOffice) {
    //   break;
    // } else {

    // }
  //}
}

FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  Args args = {Create, sid, amount, NULL};
  Job *task = new Job(args);
  jobQueue.push_back(task);
  if(!jobCond.empty())
    jobCond.signal();
  printer.print(Printer::WATCardOffice, 'C', sid, amount);
  return task->result;
}

FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
  Args args = {Transfer, sid, amount, card};
  Job *task = new Job(args);
  jobQueue.push_back(task);
  if (!jobCond.empty())
    jobCond.signal();
  printer.print(Printer::WATCardOffice, 'c', sid, amount);
  return task->result;
}

WATCardOffice::Job* WATCardOffice::requestWork(){
  if (jobQueue.empty())
    jobCond.wait();
  Job* task = jobQueue[0];
  printer.print(Printer::WATCardOffice, 'W');
  jobQueue.erase(jobQueue.begin());
  return task;
}
