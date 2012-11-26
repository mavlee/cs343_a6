#ifndef Q1PARENT_H
#define Q1PARENT_H

#include <uC++.h>

_Task Parent {
  void main();
  public:
  Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
