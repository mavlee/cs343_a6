#include <uC++.h>
#include "q1vendingmachine.h"
#include "q1printer.h"
#include "q1nameserver.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt) {
  this->numVendingMachines = numVendingMachines;
  this->numStudents = numStudents;
  machineCount = 0;
  machines = new VendingMachine *[numVendingMachines];
  printer.print(Printer::NameServer, 'S');
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
  printer.print(Printer::NameServer, 'R', machineCount);
  machines[machineCount] = vendingmachine;
  machineCount++;
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
  printer.print(Printer::NameServer, 'N', id % (machineCount));
  return machines[id % (machineCount)];
}

VendingMachine** NameServer::getMachineList() {
  return machines;
}

void NameServer::main() {
  while (1) {
    _Accept(~NameServer) {
      break;
    } else {

    }
  }
}

NameServer::~NameServer() {

  for (unsigned int i = 0; i < numVendingMachines; i++)
    delete machines[i];
  delete machines;
  printer.print(Printer::NameServer, 'F');
}
