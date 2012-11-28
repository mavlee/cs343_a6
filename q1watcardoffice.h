#ifndef Q1WATCARDOFFICE_H
#define Q1WATCARDOFFICE_H

#include <uC++.h>
#include "q1watcard.h"

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
  private:
    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    /*
    struct Job {        // marshalled arguments and return future
      Args args;        // call arguments (YOU DEFINE "Args")
      FWATCard result;      // return future
      Job( Args args ) : args( args ) {}
    };
    */
    _Task Courier { };      // communicates with bank

    void main();
  public:
    //_Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    //FWATCard create( unsigned int sid, unsigned int amount );
    //FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    //Job *requestWork();
};

#endif
