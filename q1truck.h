#ifndef Q1TRUCk_H
#define Q1TRUCK_H

#include <uC++.h>

// forward declarations
_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;
_Task VendingMachine;

_Task Truck {
  private:
    Printer &printer;               // printer
    NameServer &nameServer;         // name server
    BottlingPlant &bottlingPlant;   // bottling plant
    unsigned int numVendingMachines;// number of vending machines
    unsigned int maxStockPerFlavour;// max per flavour a machine can hold
    VendingMachine **machines;      // holds locations of machines for the truck
    unsigned int *inventory;        // the truck's current inventory
    bool hasCargo();                // checks if the truck still has cargo
    void main();                    // main function
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
};

#endif
