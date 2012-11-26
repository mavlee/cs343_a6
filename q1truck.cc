#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "MPRNG.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt),
      nameServer(nameServer), bottlingPlant(plant) {
  this->numVendingMachines = numVendingMachines;
  this->maxStockPerFlavour = maxStockPerFlavour;
}

void Truck::main() {
  // fill this stuff out
}
