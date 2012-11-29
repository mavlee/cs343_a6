#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "q1vendingmachine.h"
#include "q1truck.h"
#include "MPRNG.h"

/********* Truck ************
 * Purpose: creates the truck
 * Returns: void
 * Arguments: prt - the printer
 *            nameServer - name server for getting machine locations
 *            plant - the bottling plant that the truck gets stock from
 *            numVendingMachines - number of vending machines
 *            maxStockPerFlavour - amount of each flavour a machine can hold
 ***************************/
Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt),
      nameServer(nameServer), bottlingPlant(plant) {
  this->numVendingMachines = numVendingMachines;
  this->maxStockPerFlavour = maxStockPerFlavour;

  // 4 different flavours of soda
  inventory = new unsigned int[4];
  for (unsigned int i = 0; i < 4; i++)
    inventory[i] = 0;
}

/********* destructor ************
 * Purpose: cleanup of the truck
 * Returns: void
 ***************************/
Truck::~Truck() {
  delete inventory;
}

/********* hasCargo ************
 * Purpose: checks if the truck still has cargo to ship out
 * Returns: bool - true if the truck still has cargo, false otherwise
 * Arguments: none
 ***************************/
bool Truck::hasCargo() {
  for (unsigned int i = 0; i < 4; i++)
    if (inventory[i] > 0)
      return true;
  return false;
}

/********* main ************
 * Purpose: simulates distribution of soda to vending machines
 * Returns: void
 * Arguments: none
 ***************************/
void Truck::main() {
  printer.print(Printer::Truck, 'S');

  // get the locations of the vending machines
  machines = nameServer.getMachineList();
  unsigned int startingMachine = 0;
  unsigned int currentMachine = 0;

  // keep delivering until plant is closing down
  while (true) {
    yield(rng(1, 10));
    bool isPlantClosing = bottlingPlant.getShipment(inventory);

    // plant is closing down
    if (isPlantClosing)
      break;

    // picked up shipment message
    unsigned int totalStock = 0;
    for (unsigned int i = 0; i < 4; i++)
      totalStock += inventory[i];
    printer.print(Printer::Truck, 'P', totalStock);

    // stock machines
    startingMachine = currentMachine;
    do {
      unsigned int *machineStock = machines[currentMachine]->inventory();
      printer.print(Printer::Truck, 'd', currentMachine, inventory[0] + inventory[1] + inventory[2] + inventory[3]);
      bool successful = true;
      int sodasMissing = 0;
      int sodasLeft = 0;

      // 4 sodas
      for (unsigned int i = 0; i < 4; i++) {
        machineStock[i] += inventory[i];
        inventory[i] = 0;
        if (machineStock[i] >= maxStockPerFlavour) {
          inventory[i] = machineStock[i] - maxStockPerFlavour;
          machineStock[i] = maxStockPerFlavour;
        } else {
          sodasMissing += maxStockPerFlavour - machineStock[i];
          successful = false;
        }
        sodasLeft += inventory[i];
      }

      // stocking messages and alert machine restocking is done
      if (!successful)
        printer.print(Printer::Truck, 'U', currentMachine, sodasMissing);
      printer.print(Printer::Truck, 'D', currentMachine, sodasLeft);
      machines[currentMachine]->restocked();

      // find the next machine
      if (currentMachine == numVendingMachines - 1)
        currentMachine = 0;
      else
        currentMachine++;
    // delivery run continues until full loop is done or out of cargo
    } while (hasCargo() && startingMachine != currentMachine);
  }

  printer.print(Printer::Truck, 'F');
}
