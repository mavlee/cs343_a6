#include <uC++.h>
#include "q1bank.h"

Bank::Bank( unsigned int numStudents ) {
  this->numStudents = numStudents;
  amounts = new unsigned int[numStudents];
  for (unsigned int i = 0; i < numStudents; i++)
    amounts[i] = 0;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
  amounts[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
  amounts[id] -= amount;
}
