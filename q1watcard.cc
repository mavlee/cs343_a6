#include <uC++.h>
#include "q1watcard.h"

/********** WATCard ***********
 * Purpose: constructor for watcard
 * Returns: void
 * Arguments: none
 ***************************/
WATCard::WATCard() {
  balance = 0;
}

/********** deposit ***********
 * Purpose: gives money to the card
 * Returns: void
 * Arguments: none
 ***************************/
void WATCard::deposit( unsigned int amount ) {
  balance += amount;
}

/********** withdraw ***********
 * Purpose: takes money from the card
 * Returns: void
 * Arguments: none
 ***************************/
void WATCard::withdraw( unsigned int amount ) {
  balance -= amount;
}

/********** getBalance ***********
 * Purpose: finds the balance of a card
 * Returns: the balance of the card
 * Arguments: none
 ***************************/
unsigned int WATCard::getBalance() {
  return balance;
}
