#ifndef Q1VENDINGMACHINE_H
#define Q1VENDINGMACHINE_H

#include <uC++.h>

// forward declarations
_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
  private:
    Printer &printer;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int *stock;
    void main();
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
