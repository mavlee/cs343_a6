#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "q1truck.h"
#include "MPRNG.h"

/********* BottlingPlant ************
 * Purpose: creates the bottling plant
 * Returns: void
 * Arguments: prt - the printer
 *            nameServer - name server for getting machine locations
 *            numVendingMachines - number of vending machines
 *            maxShippedPerFlavour - the max generated of each flavour
 *            maxStockPerFlavour - amount of each flavour a machine can hold
 *            timeBetweenShipments - the amount to delay per shipment run
 ***************************/
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

/********* getShipment ************
 * Purpose: creates the bottling plant
 * Returns: bool - true if the plant is closing down, false otherwise (cargo is loaded)
 * Arguments: cargo[] - array to load the generated shipment into
 ***************************/
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

/********* destructor ************
 * Purpose: cleanup of the bottling plant
 * Returns: void
 ***************************/
BottlingPlant::~BottlingPlant() {
  delete generatedStock;
}

/********* main ************
 * Purpose: creates the truck, then periodically generates soda for the truck to pick up
 * Returns: void
 ***************************/
void BottlingPlant::main() {
  unsigned int totalProduction = 0;
  printer.print(Printer::BottlingPlant, 'S');
  // create truck
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

  // loop of soda creation
  while (true) {
    _Accept(~BottlingPlant) {
      // destructor is accepted, wait for the truck to complete before finishing
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
