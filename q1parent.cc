#include <uC++.h>
#include "q1parent.h"
#include "q1bank.h"
#include "q1printer.h"
#include "MPRNG.h"

/********** Parent ***********
 * Purpose: creates the parent
 * Returns: void
 * Arguments: prt - the printer
 *            bank - the bank
 *            numStudents - number of students
 *            parentalDelay - delay before the parent deposits more money
 ***************************/
Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) : printer(prt), bank(bank) {
  this->numStudents = numStudents;
  this->parentalDelay = parentalDelay;
  printer.print(Printer::Parent, 'S');
}


/********** destructor ***********
 * Purpose: cleans up the parent and gives the finish message
 * Returns: void
 * Arguments: none
 ***************************/
Parent::~Parent() {
  printer.print(Printer::Parent, 'F');
}

/********** main ***********
 * Purpose: the parent gives money to a random student every parentalDelay
 * Returns: void
 * Arguments: none
 ***************************/
void Parent::main() {
  while (true) {
    // keep going until the main destroys the parent
    _Accept (~Parent) {
      break;
    } else {
      // generate random amount of money, a student to give it to
      unsigned int money = rng(1,3);
      unsigned int student = rng(numStudents-1);
      yield(parentalDelay);
      bank.deposit(student, money);
      printer.print(Printer::Parent, 'D', student, money);
    }
  }
}
