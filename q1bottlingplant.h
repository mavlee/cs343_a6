#ifndef Q1BOTTLINGPLANT_H
#define Q1BOTTLINGPLANT_H

#include <uC++.h>

_Task BottlingPlant {
  void main();
  public:
  BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments );
  bool getShipment( unsigned int cargo[] );
};

#endif
