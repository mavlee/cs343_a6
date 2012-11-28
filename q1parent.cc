#include <uC++.h>
#include "q1parent.h"
#include "q1bank.h"
#include "q1printer.h"
#include "MPRNG.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) : printer(prt), bank(bank) {
  this->numStudents = numStudents;
  this->parentalDelay = parentalDelay;
}

void Parent::main() {
  while (true) {
    _Accept(~Parent) {
      break;
    } else {
      unsigned int money = rng(1,3);
      unsigned int student = rng(numStudents);
      yield(parentalDelay);
      bank.deposit(student, money);
    }
  }
}
