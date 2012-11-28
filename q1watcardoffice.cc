#include <uC++.h>
#include "q1printer.h"
#include "q1bank.h"
#include "q1watcard.h"
#include "q1watcardoffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), bank(bank) {
  this->numCouriers = numCouriers;
}

void WATCardOffice::main() {
}
