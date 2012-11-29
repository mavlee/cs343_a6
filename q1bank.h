#ifndef Q1BANK_H
#define Q1BANK_H

#include <uC++.h>

_Monitor Bank {
  private:
    unsigned int *amounts;    // holds the balance for each student
    unsigned int numStudents; // the number of students
    uCondition *noMoney;      // array of conditions when a student has no money
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
