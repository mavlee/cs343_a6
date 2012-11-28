#ifndef Q1BOTTLINGPLANT_H
#define Q1BOTTLINGPLANT_H

#include <uC++.h>

_Monitor Printer;
_Task NameServer;

_Task BottlingPlant {
  private:
    Printer &printer;
    NameServer &nameServer;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int numVendingMachines;
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
