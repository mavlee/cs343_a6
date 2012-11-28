#include "q1student.h"
#include "q1printer.h"
#include "q1watcardoffice.h"
#include "q1nameserver.h"
#include "MPRNG.h"

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
  unsigned int id, unsigned int maxPurchases) : printer(prt), nameServer(nameServer), office(cardOffice) {
  this->id = id;
  purchasesLeft = rng(1, maxPurchases);
  favFlavour = rng(3);
}

void Student::main() {
  // Get a watcard from the watcard office
  while (purchasesLeft) {
    // Buy a drink
    purchasesLeft--;
  }
}
