#include "q1student.h"
#include "q1printer.h"
#include "q1watcardoffice.h"
#include "q1nameserver.h"
#include "q1watcard.h"
#include "q1vendingmachine.h"
#include "MPRNG.h"

/********* Student ************
 * Purpose: creates the student
 * Returns: void
 * Arguments: prt - the printer
 *            nameServer - name server for getting machine locations
 *            cardOffice - the watcard office
 *            id - id of the student
 *            maxPurchases - the maximum number of purchases the student will have to make
 ***************************/
Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
  unsigned int id, unsigned int maxPurchases) : printer(prt), nameServer(nameServer), office(cardOffice) {
  this->id = id;
  // the number of purchases to make is random from 1 to maxPurchases
  purchasesLeft = rng(1, maxPurchases);
  favFlavour = rng(3);
  printer.print(Printer::Student, id, 'S', favFlavour, purchasesLeft);
}

/********* main ************
 * Purpose: does the actions of the student, picking a machine and purchasing
 *          soda.  Also handles watcard getting lost
 * Returns: void
 * Arguments: none
 ***************************/
void Student::main() {
  // Get a watcard from the watcard office
  VendingMachine *myVend = NULL;
  FWATCard card;
  while (purchasesLeft) {
    try {
      // create the card and pick a machine
      card = office.create(id, 5);
      if (myVend == NULL) {
        myVend = nameServer.getMachine(id);
        printer.print(Printer::Student, id, 'V', myVend->getId());
      }
      while (purchasesLeft) {
        // Buy a drink
        yield(rng(1,10));
        VendingMachine::Status buyResult = myVend->buy(VendingMachine::Flavours(favFlavour), *card());
        if (buyResult == VendingMachine::FUNDS) {
          card = office.transfer(id, myVend->cost() + 5, card());
        } else if (buyResult == VendingMachine::STOCK) {
          myVend = nameServer.getMachine(id);
        } else if (buyResult == VendingMachine::BUY) {
          printer.print(Printer::Student, id, 'B', card()->getBalance());
          purchasesLeft--;
        }
      }
    // if the watcard is lost, start the process again
    } catch (WATCardOffice::Lost) {
      printer.print(Printer::Student, id, 'L');
    }
  }
  delete card;
  printer.print(Printer::Student, id, 'F');
}
