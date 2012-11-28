#include <uC++.h>
#include "q1vendingmachine.h"
#include "q1printer.h"
#include "q1nameserver.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt) {
  this->numVendingMachines = numVendingMachines;
  this->numStudents = numStudents;
  //machines = new VendingMachine *[numVendingMachines];
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
  //machines[0] = vendingmachine;
}

VendingMachine NameServer::*getMachine( unsigned int id ) {
  //return machines[0];
}

VendingMachine NameServer::**getMachineList() {
  //return machines;
}

void NameServer::main() {

}

NameServer::~NameServer() {
  /*
  for (unsigned int i = 0; i < numVendingMachines; i++)
    delete machines[i];
  delete machines;
  */
}
