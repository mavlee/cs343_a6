#ifndef Q1PARENT_H
#define Q1PARENT_H

#include <uC++.h>

// forward declarations
_Monitor Printer;
_Monitor Bank;

_Task Parent {
  private:
    Printer &printer;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent();
};

#endif
