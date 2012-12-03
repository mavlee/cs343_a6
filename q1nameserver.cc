#include <uC++.h>
#include "q1vendingmachine.h"
#include "q1printer.h"
#include "q1nameserver.h"

/******* NameServer ********
 * Purpose: NameServer constructor
 * Returns: void
 * Arguments: &prt - reference to printer
 *            numVendingMachines - number of vending machines
 *            numStudents - number of students
 ***************************/
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt) {
  this->numVendingMachines = numVendingMachines;
  this->numStudents = numStudents;
  machineCount = 0;
  machines = new VendingMachine *[numVendingMachines];
  assignedCount = -1;
  printer.print(Printer::NameServer, 'S');
}

/******* VMregister ********
 * Purpose: registers a vending machine with name server
 * Returns: void
 * Arguments: *vendingmachine - pointer to a vending machine
 ***************************/
void NameServer::VMregister( VendingMachine *vendingmachine ) {
  printer.print(Printer::NameServer, 'R', machineCount);
  // register machine and increment the count
  machines[machineCount] = vendingmachine;
  machineCount++;
}

/******* getMachine ********
 * Purpose: assigns a machine to a student and return sit
 * Returns: VendingMachine*
 * Arguments: id - student id
 ***************************/
VendingMachine* NameServer::getMachine( unsigned int id ) {
  assignedCount++;
  printer.print(Printer::NameServer, 'N', id, assignedCount % (machineCount));
  // assign machines in a circular fashion
  return machines[assignedCount % (machineCount)];
}

/***** getMachineList ******
 * Purpose: returns array of vending machines
 * Returns: VendingMachine**
 * Arguments: none
 ***************************/
VendingMachine** NameServer::getMachineList() {
  return machines;
}

/********* main ************
 * Purpose: nameserver's main
 * Returns: void
 * Arguments: none
 ***************************/
void NameServer::main() {

}

/********* ~main ***********
 * Purpose: nameserver's destructor
 * Returns: void
 * Arguments: none
 ***************************/
NameServer::~NameServer() {
  delete machines;
  printer.print(Printer::NameServer, 'F');
}
