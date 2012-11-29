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

  plantClosing = false;
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {
  if (plantClosing)
    return true;

  // todo figure out when to return true
  for (unsigned int i = 0; i < 4; i++) {
    cargo[i] = generatedStock[i];
    generatedStock[i] = 0;
  }
  printer.print(Printer::BottlingPlant, 'P');
  return false;
}

BottlingPlant::~BottlingPlant() {
  delete generatedStock;
}

void BottlingPlant::main() {
  unsigned int totalProduction = 0;
  printer.print(Printer::BottlingPlant, 'S');
  Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

  // first production run
  yield(timeBetweenShipments);
  // produce soda
  totalProduction = 0;
  for (unsigned int i = 0; i < 4; i++) {
    generatedStock[i] = rng(maxShippedPerFlavour);
    totalProduction += generatedStock[i];
  }
  printer.print(Printer::BottlingPlant, 'G', totalProduction);


  while (true) {
    _Accept(~BottlingPlant) {
      plantClosing = true;
      _Accept(getShipment);
      break;
    } or _Accept(getShipment) {
      yield(timeBetweenShipments);

      // produce soda
      totalProduction = 0;
      for (unsigned int i = 0; i < 4; i++) {
        generatedStock[i] = rng(maxShippedPerFlavour);
        totalProduction += generatedStock[i];
      }
      printer.print(Printer::BottlingPlant, 'G', totalProduction);
    }
  }
  printer.print(Printer::BottlingPlant, 'F');
}
