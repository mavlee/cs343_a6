#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "MPRNG.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments ) : printer(prt), nameServer(nameServer) {
  this->maxShippedPerFlavour = maxShippedPerFlavour;
  this->maxStockPerFlavour = maxStockPerFlavour;
  this->timeBetweenShipments timeBetweenShipments;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
  return false;
}

void BottlingPlant::main() {

}
