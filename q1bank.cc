#include <uC++.h>
#include "q1bank.h"

/********** Bank ***********
 * Purpose: constructor for bank
 * Returns: Bank
 * Arguments: numStudents - number of students
 ***************************/
Bank::Bank( unsigned int numStudents ) {
  this->numStudents = numStudents;
  amounts = new unsigned int[numStudents];
  for (unsigned int i = 0; i < numStudents; i++)
    amounts[i] = 0;

  noMoney = new uCondition[numStudents];
}

/********* ~Bank ***********
 * Purpose: destructor for bank; frees allocated objects
 * Returns: void
 * Arguments:
 ***************************/
Bank::~Bank() {
  delete [] amounts;
  delete [] noMoney;
}

/******** deposit **********
 * Purpose: deposits money from a student's account
 * Returns: void
 * Arguments: id - id of student's account
              amount - amount to deposit
 ***************************/
void Bank::deposit( unsigned int id, unsigned int amount ) {
  amounts[id] += amount;
  if (!noMoney[id].empty())
    noMoney[id].signal();
}

/******** withdraw **********
 * Purpose: withdraws money from a student's account, blocks on
            insufficient funds
 * Returns: void
 * Arguments: id - id of student's account
              amount - amount to withdraw
 ***************************/
void Bank::withdraw( unsigned int id, unsigned int amount ) {
  while(amounts[id] < amount) {
    noMoney[id].wait();
  }
  amounts[id] -= amount;
}
