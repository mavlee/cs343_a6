#ifndef Q1BOTTLINGPLANT_H
#define Q1BOTTLINGPLANT_H

#include <uC++.h>

_Monitor Printer;
_Task NameServer;

_Task BottlingPlant {
  private:
    Printer &printer;                   // printer
    NameServer &nameServer;             // name server
    unsigned int *generatedStock;       // holds the soda generated by the bottling plant
    unsigned int maxShippedPerFlavour;  // max amount per flavour
    unsigned int maxStockPerFlavour;    // max of each flavour a machine can hold
    unsigned int timeBetweenShipments;  // amount of delay between shipments
    unsigned int numVendingMachines;    // number of vending machines
    bool plantClosing;                  // indicates if the plant is going to shut down
    void main();                        // main function
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
      unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
      unsigned int timeBetweenShipments );
    ~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};

#endif
