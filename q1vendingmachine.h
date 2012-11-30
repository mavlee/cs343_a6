#ifndef Q1VENDINGMACHINE_H
#define Q1VENDINGMACHINE_H

#include <uC++.h>

// forward declarations
_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
  private:
    Printer &printer;                 // printer
    NameServer &nameServer;           // name server
    unsigned int id;                  // machine id
    unsigned int sodaCost;            // soda cost
    unsigned int maxStockPerFlavour;  // maximum of each type of soda
    unsigned int *stock;              // array holding amount of soda

    bool stocking;                    // whether or not the machine is being stocked at the moment
    uCondition stockLock;             // lock to enforce machine not selling soda

    void main();                      // main function
  public:
    enum Flavours { BlackCherry, CreamSoda, RootBeer, Lime };      // flavours of soda (YOU DEFINE)
    enum Status { BUY, STOCK, FUNDS };    // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
        unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
