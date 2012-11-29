#ifndef Q1PARENT_H
#define Q1PARENT_H

#include <uC++.h>

// forward declarations
_Monitor Printer;
_Monitor Bank;

_Task Parent {
  private:
    Printer &printer;           // printer
    Bank &bank;                 // bank
    unsigned int numStudents;   // number of students
    unsigned int parentalDelay; // delay before the parent gives more monies
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent();
};

#endif
