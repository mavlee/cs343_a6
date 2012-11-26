#ifndef Q1CONFIGPARAMS_H
#define Q1CONFIGPARAMS_H

#include <uC++.h>
#include <fstream>
#include <string>

struct ConfigParams {
    unsigned int sodaCost;
    unsigned int numStudents;
    unsigned int maxPurchases;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    unsigned int maxShippedPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int parentalDelay;
    unsigned int numCouriers;
};

void processConfigFile( const char *configFile, ConfigParams &cParams);

#endif
