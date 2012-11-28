#ifndef Q1PRINTER_H
#define Q1PRINTER_H

#include <uC++.h>

_Monitor Printer {
  private:
    unsigned int numObjects;
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    char *status;                 // holds the state type
    int **statusValues; // holds the values for various states
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
    void displayStatus();
    void printFinish();
};

#endif
