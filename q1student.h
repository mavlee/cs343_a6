#ifndef Q1STUDENT_H
#define Q1STUDENT_H

#include <uC++.h>

// forward declarations
class Printer;
_Task WATCardOffice;
_Task NameServer

_Task Student {
  void main();
  public:
  Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
      unsigned int maxPurchases );
};

#endif
