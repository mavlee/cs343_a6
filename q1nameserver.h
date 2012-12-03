#ifndef Q1NAMESERVER_H
#define Q1NAMESERVER_H

#include <uC++.h>

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
  private:
    void main();
    Printer &printer;                       // printer
    unsigned int numVendingMachines;        // number of machines
    unsigned int numStudents;               // number of students
    unsigned int machineCount;              // number of machines registered
    int assignedCount;                      // number of machines assigned
    VendingMachine **machines;              // array of machines
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
    ~NameServer();
};

#endif
