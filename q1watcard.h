#ifndef Q1WATCARD_H
#define Q1WATCARD_H

#include <uC++.h>
#include <uFuture.h>

class WATCard {
  private:
    unsigned int balance;           // holds the balance of a card
    WATCard( const WATCard & );     // prevent copying
    WATCard &operator=( const WATCard & );
  public:
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};
typedef Future_ISM<WATCard *> FWATCard;   // future WATCard pointer

#endif
