#ifndef Q1WATCARDOFFICE_H
#define Q1WATCARDOFFICE_H

#include <uC++.h>
#include "q1watcard.h"
#include <vector>


_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
    enum JobType {Create, Transfer, Destroy};     // Different types of jobs

    typedef struct {
      JobType type;                               // indicate job type
      unsigned int sid;                           // student id
      unsigned int amount;                        // amount of money
      WATCard *card;                              // pointer to watcard
    } Args;

    struct Job {                                  // marshalled arguments and return future
      Args args;                                  // job arguments
      FWATCard result;                            // return future
      Job( Args args ) : args( args ) {}
    };

    _Task Courier {
      private:
        Bank &bank;                               // reference to bank
        Printer &printer;                         // reference to printer
        WATCardOffice *office;                    // pointer to office
        unsigned int id;                          // courier id
        void main();
      public:
        Courier(Bank &bank, Printer &prt, WATCardOffice *office, unsigned int cid);
        ~Courier();
    };      // communicates with bank

    Printer &printer;                             // printer
    Bank &bank;                                   // bank
    unsigned int numCouriers;                     // number of couriers
    Courier **couriers;                           // courier array
    uCondition jobCond;                           // condition to block couriers when no jobs

    std::vector<Job*> jobQueue;                   // queue of jobs

    void main();

  public:
    _Event Lost {};

    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
