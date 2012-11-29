#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "q1vendingmachine.h"
#include "q1truck.h"
#include "MPRNG.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt),
      nameServer(nameServer), bottlingPlant(plant) {
  this->numVendingMachines = numVendingMachines;
  this->maxStockPerFlavour = maxStockPerFlavour;

  // 4 different flavours of soda
  inventory = new unsigned int[4];
  for (unsigned int i = 0; i < 4; i++)
    inventory[i] = 0;
  currentMachine = 0;
}

bool Truck::hasCargo() {
  for (unsigned int i = 0; i < 4; i++)
    if (inventory[i] > 0)
      return true;
  return false;
}


void Truck::main() {
  // fill this stuff out
  printer.print(Printer::Truck, 'S');
  machines = nameServer.getMachineList();
  unsigned int startingMachine = 0;

  while (true) {
    yield(rng(1, 10));
    bool isPlantClosing = bottlingPlant.getShipment(inventory);
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
      printer.print(Printer::Truck, 'd');
      unsigned int *machineStock = machines[currentMachine]->inventory();
      bool successful = false;
      int sodasMissing = 0;
      int sodasLeft = 0;
      // 4 sodas
      for (unsigned int i = 0; i < 4; i++) {
        machineStock[i] += inventory[i];
        inventory[i] = 0;
        if (machineStock[i] >= maxStockPerFlavour) {
          inventory[i] = machineStock[i] - maxStockPerFlavour;
          machineStock[i] = maxStockPerFlavour;
          successful = true;
        } else {
          sodasMissing += maxStockPerFlavour - machineStock[i];
        }
        sodasLeft += inventory[i];
      }
      machines[currentMachine]->restocked();

      printer.print(Printer::Truck, 'U', currentMachine, sodasMissing);
      printer.print(Printer::Truck, 'D', currentMachine, sodasLeft);

      if (currentMachine == numVendingMachines - 1)
        currentMachine = 0;
      else
        currentMachine++;
    } while (hasCargo() && startingMachine != currentMachine);
  }

  printer.print(Printer::Truck, 'F');
}
