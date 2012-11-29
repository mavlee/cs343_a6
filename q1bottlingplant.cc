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

  // 4 different kinds of soda
  generatedStock = new unsigned int[4];
  for (unsigned int i = 0; i < 4; i++)
    generatedStock[i] = 0;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
  // todo figure out when to return true
  for (unsigned int i = 0; i < 4; i++) {
    cargo[i] = generatedStock[i];
    generatedStock[i] = 0;
  }
  printer.print(Printer::BottlingPlant, 'P');
  productionLock.signal();
  return false;
}

void BottlingPlant::main() {
  unsigned int totalProduction = 0;
  printer.print(Printer::BottlingPlant, 'S');
  Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

  while (true) {
    // _Accept(~BottlingPlant) {
    //   break;
    // } else {
      yield(timeBetweenShipments);

      // produce soda
      totalProduction = 0;
      for (unsigned int i = 0; i < 4; i++) {
        generatedStock[i] = rng(maxShippedPerFlavour);
        totalProduction += generatedStock[i];
      }

      printer.print(Printer::BottlingPlant, 'G', totalProduction);
      productionLock.wait();
    }
  //}
  printer.print(Printer::BottlingPlant, 'F');
}
