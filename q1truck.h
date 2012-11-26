#ifndef Q1TRUCk_H
#define Q1TRUCK_H

#include <uC++.h>

_Task Truck {
  void main();
  public:
  Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
