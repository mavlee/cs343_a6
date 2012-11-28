#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "q1truck.h"
#include "MPRNG.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments ) : printer(prt), nameServer(nameServer) {
  this->maxShippedPerFlavour = maxShippedPerFlavour;
  this->maxStockPerFlavour = maxStockPerFlavour;
  this->timeBetweenShipments = timeBetweenShipments;
  this->numVendingMachines = numVendingMachines;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
  return false;
}

void BottlingPlant::main() {
  Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);
}
