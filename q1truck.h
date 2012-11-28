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
    Printer &printer;
    NameServer &nameServer;
    BottlingPlant &bottlingPlant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    VendingMachine **machines;
    unsigned int *inventory;
    unsigned int currentMachine;
    bool hasCargo();
    void main();
  public:
  Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
