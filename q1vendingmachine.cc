#include <uC++.h>
#include "q1printer.h"
#include "q1nameserver.h"
#include "q1vendingmachine.h"
#include "q1watcard.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer,
    unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer) {
  this->id = id;
  this->sodaCost = sodaCost;
  this->maxStockPerFlavour = maxStockPerFlavour;

  // init stock
  stock = new unsigned int[4];
  for (unsigned int i = 0; i < 4; i++)
    stock[i] = 0;

  printer.print(Printer::Vending, id, 'S');

  nameServer.VMregister(this);

  stocking = false;
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  if (card.getBalance() < sodaCost)
    return FUNDS;
  if (stock[flavour] == 0)
    return STOCK;
  stock[flavour]--;
  printer.print(Printer::Vending, id, 'B', flavour, stock[flavour]);
  return BUY;
}

void VendingMachine::main() {
  while (1) {
    _Accept(~VendingMachine) {
      break;
    } _When(!stocking) _Accept(buy) {

    } else {

    }
  }
}

unsigned int* VendingMachine::inventory() {
  stocking = true;
  printer.print(Printer::Vending, id, 'r');
  return stock;
}

void VendingMachine::restocked() {
  stocking = false;
  printer.print(Printer::Vending, id, 'R');
}

unsigned int VendingMachine::cost() {
  return sodaCost;
}

unsigned int VendingMachine::getId() {
  return id;
}

VendingMachine::~VendingMachine() {
  delete stock;
  printer.print(Printer::Vending, id, 'F');
}
