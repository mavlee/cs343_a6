#include "q1student.h"
#include "MPRNG.h"

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice,
  unsigned int id, unsigned int maxPurchases) : printer(prt), nameServer(nameServer), office(cardOffice) {
  this->id = id;
  purchasesLeft = rng(1, maxPurchases);
  favFlavour = rng(3);
}

void Student::main() {
  while (purchasesLeft) {
    // Buy a drink
    purchasesLeft--;
  }
}
