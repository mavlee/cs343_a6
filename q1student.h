#ifndef Q1STUDENT_H
#define Q1STUDENT_H

#include <uC++.h>

// forward declarations
_Monitor Printer;
_Task WATCardOffice;
_Task NameServer;

_Task Student {
  private:
    Printer &printer;           // printer
    NameServer &nameServer;     // name server
    WATCardOffice &office;      // watcard office
    unsigned int id;            // student's id
    unsigned int purchasesLeft; // how many more sodas to buy
    unsigned int favFlavour;    // the student's favourite flavour
    void main();                // main function
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
      unsigned int maxPurchases );
};

#endif
