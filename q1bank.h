#ifndef Q1BANK_H
#define Q1BANK_H

#include <uC++.h>

_Monitor Bank {
  private:
    unsigned int *amounts;
    unsigned int numStudents;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
