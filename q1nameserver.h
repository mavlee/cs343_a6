#ifndef Q1NAMESERVER_H
#define Q1NAMESERVER_H

#include <uC++.h>

_Task VendingMachine;
_Monitor Printer;

_Task NameServer {
  private:
    void main();
    Printer &printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    VendingMachine **machines;
    unsigned int *inventory;
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
    ~NameServer();
};

#endif
