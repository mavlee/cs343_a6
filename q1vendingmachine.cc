#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1vendingmachine.h"
#include "q1watcard.h"

/********* VendingMachine ************
 * Purpose: creates the vending machine
 * Returns: void
 * Arguments: prt - the printer
 *            nameServer - name server for getting machine locations
 *            id - the id of the machine
 *            sodaCost - the price of soda
 *            maxStockPerFlavour - amount of each flavour a machine can hold
 ***************************/
VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer,
    unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer) {
  this->id = id;
  this->sodaCost = sodaCost;
  this->maxStockPerFlavour = maxStockPerFlavour;

  // init stock
  stock = new unsigned int[4];
  for (unsigned int i = 0; i < 4; i++)
    stock[i] = 0;

  printer.print(Printer::Vending, id, 'S', sodaCost);
  nameServer.VMregister(this);
  stocking = false;
}

/********* buy ************
 * Purpose: student calls this to try to buy soda
 * Returns: the status of the purchase attempt
 * Arguments: flavour - which soda to buy
 *            card - the watcard from which to get money
 ***************************/
VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  if (stocking)
    stockLock.wait();

  if (card.getBalance() < sodaCost)
    return FUNDS;
  if (stock[flavour] == 0)
    return STOCK;
  card.withdraw(sodaCost);
  stock[flavour]--;
  printer.print(Printer::Vending, id, 'B', flavour, stock[flavour]);
  return BUY;
}

/********* main ************
 * Purpose: does nothing
 * Returns: void
 * Arguments: none
 ***************************/
void VendingMachine::main() {
}

/********* inventory ************
 * Purpose: gets the soda inventory of the machine
 * Returns: an array pointer for the soda inventory
 * Arguments: none
 ***************************/
unsigned int* VendingMachine::inventory() {
  stocking = true;
  printer.print(Printer::Vending, id, 'r');
  return stock;
}

/********* restocked ************
 * Purpose: truck calls to tell machine students can buy again
 * Returns: void
 * Arguments: none
 ***************************/
void VendingMachine::restocked() {
  stocking = false;
  while (!stockLock.empty())
    stockLock.signal();
  printer.print(Printer::Vending, id, 'R');
}

/********* cost ************
 * Purpose: gets the price of a soda for the machine
 * Returns: the cost of a soda for the machine
 * Arguments: none
 ***************************/
unsigned int VendingMachine::cost() {
  return sodaCost;
}

/********* getId ************
 * Purpose: gets the id of the vending machine
 * Returns: the id of the machine
 * Arguments: none
 ***************************/
unsigned int VendingMachine::getId() {
  return id;
}

/********* destructor ************
 * Purpose: cleans up the vending machine and prints the finish message
 * Returns: void
 * Arguments: none
 ***************************/
VendingMachine::~VendingMachine() {
  delete stock;
  printer.print(Printer::Vending, id, 'F');
}
