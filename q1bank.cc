#include <uC++.h>
#include "q1bank.h"

Bank::Bank( unsigned int numStudents ) {
  this->numStudents = numStudents;
  amounts = new unsigned int[numStudents];
  for (unsigned int i = 0; i < numStudents; i++)
    amounts[i] = 0;

  noMoney = new uCondition[numStudents];
}

Bank::~Bank() {
  delete [] amounts;
  delete [] noMoney;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
  amounts[id] += amount;
  if (!noMoney[id].empty())
    noMoney[id].signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
  while(amounts[id] < amount) {
    noMoney[id].wait();
  }
  amounts[id] -= amount;
}
