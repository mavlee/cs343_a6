#ifndef Q1BOTTLINGPLANT_H
#define Q1BOTTLINGPLANT_H

#include <uC++.h>

_Monitor Printer;
_Task NameServer;

_Task BottlingPlant {
  private:
    Printer &printer;
    NameServer &nameServer;
    uCondition productionLock;
    unsigned int *generatedStock;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int numVendingMachines;
    bool plantClosing;
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments );
    ~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};

#endif
