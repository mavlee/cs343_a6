#ifndef Q1WATCARDOFFICE_H
#define Q1WATCARDOFFICE_H

#include <uC++.h>
#include "q1watcard.h"
#include <vector>


_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
  private:
    enum JobType {Create, Transfer};

    typedef struct {
      JobType type;
      unsigned int sid;
      unsigned int amount;
      WATCard *card;
      // some arguments
    } Args;

    struct Job {        // marshalled arguments and return future
      Args args;        // call arguments (YOU DEFINE "Args")
      FWATCard result;      // return future
      Job( Args args ) : args( args ) {}
    };

    _Task Courier {
      private:
        Bank &bank;
        Printer &printer;
        unsigned int id;
        void main();
      public:
        Courier(Bank &bank, Printer &prt, unsigned int cid);
        ~Courier();
    };      // communicates with bank

    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    Courier **couriers;

    std::vector<Job*> jobQueue;

    void main();

  public:
    //_Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    //Job *requestWork();
};

#endif
