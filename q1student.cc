#include "q1student.h"
#include "q1printer.h"
#include "q1watcardoffice.h"
#include "q1nameserver.h"
#include "q1watcard.h"
#include "q1vendingmachine.h"
#include "MPRNG.h"

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
  unsigned int id, unsigned int maxPurchases) : printer(prt), nameServer(nameServer), office(cardOffice) {
  this->id = id;
  purchasesLeft = rng(1, maxPurchases);
  favFlavour = rng(3);
  printer.print(Printer::Student, id, 'S', favFlavour, purchasesLeft);
}

void Student::main() {
  // Get a watcard from the watcard office
  FWATCard card = office.create(id, 5);
  VendingMachine *myVend = nameServer.getMachine(id);
  printer.print(Printer::Student, id, 'V', myVend->getId());
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
  printer.print(Printer::Student, id, 'F');
}
