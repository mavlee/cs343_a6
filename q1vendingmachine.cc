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
    stock[i] = '0';
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
  if (stock[flavour] == 0)
    return STOCK;
  if (card.getBalance() < sodaCost)
    return FUNDS;
  return BUY;
}

unsigned int* VendingMachine::inventory() {
  return stock;
}

void VendingMachine::restocked() {

}

unsigned int VendingMachine::cost() {
  return sodaCost;
}

unsigned int VendingMachine::getId() {
  return id;
}

VendingMachine::~VendingMachine() {
  delete stock;
}
