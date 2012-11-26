#ifndef Q1CONFIGPARAMS_H
#define Q1CONFIGPARAMS_H

#include <uC++.h>

struct ConﬁgParms {
  unsigned int sodaCost; // MSRP per bottle
  unsigned int numStudents; // number of students to create
  unsigned int maxPurchases; // maximum number of bottles a student purchases
  unsigned int numVendingMachines; // number of vending machines
  unsigned int maxStockPerFlavour; // maximum number of bottles of each ﬂavour stocked
  unsigned int maxShippedPerFlavour; // number of bottles of each ﬂavour in a shipment
  unsigned int timeBetweenShipments; // length of time between shipment pickup
  unsigned int parentalDelay; // length of time between cash deposits
  unsigned int numCouriers; // number of couriers in the pool
};
void processConﬁgFile( const char *conﬁgFile, ConﬁgParms &cparms );

#endif
