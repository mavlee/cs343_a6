#include <uC++.h>
#include "q1printer.h"
#include "q1bank.h"
#include "q1watcardoffice.h"

void WATCardOffice::Courier::main() {
  while(1) {
    _Accept(~Courier) {
      break;
    } else {
      // Doesn't work yet, delete next two lines later
      // Job *task = requestWork();
      Args testArgs = {Transfer, 0, 10, new WATCard()};
      Job *task = new Job(testArgs);

      unsigned int sid = task->args.sid;
      unsigned int amount = task->args.amount;
      Bank *bank = task->args.bank;

      // TODO: Simulate lost card

      if (task->args.type == Create) {            // This syntax is pretty ugly
          task->args.card = new WATCard();
          task->args.card->deposit(5);
      } else if (task->args.type == Transfer) {
          bank->withdraw(sid, amount);             // Block here until funds are available
          task->args.card->deposit(amount);
      }
    }
  }
}

WATCardOffice::Courier::Courier() {

}

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), bank(bank) {
  this->numCouriers = numCouriers;
  couriers = new Courier[numCouriers];
}

void WATCardOffice::main() {
  while (1) {
    _Accept(~WATCardOffice) {
      break;
    } else {}
  }
}

FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount) {
  Args args = {Create, sid, amount, NULL, &bank};
  Job *task = new Job(args);
  jobQueue.push_back(task);
  return task->result;
}

FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
  Args args = {Transfer, sid, amount, card, &bank};
  Job *task = new Job(args);
  jobQueue.push_back(task);
  return task->result;
}

// WATCardOffice::Job WATCardOffice::*requestWork(){
//   return NULL;
// }
