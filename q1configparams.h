#ifndef Q1CONFIGPARAMS_H
#define Q1CONFIGPARAMS_H

#include <uC++.h>
#include <fstream>
#include <string>

struct ConfigParams {
    unsigned int sodaCost;              // MSRP per bottle
    unsigned int numStudents;           // number of students to create
    unsigned int maxPurchases;          // maximum number of bottles a student purchases
    unsigned int numVendingMachines;    // number of vending machines
    unsigned int maxStockPerFlavour;    // maximum number of bottles of each flavour stocked
    unsigned int maxShippedPerFlavour;  // number of bottles of each flavour in a shipment
    unsigned int timeBetweenShipments;  // length of time between shipment pickup
    unsigned int parentalDelay;         // length of time between cash deposits
    unsigned int numCouriers;           // number of couriers in the pool
};

void processConfigFile( const char *configFile, ConfigParams &cParams);
bool matchParameter(std::string line, std::string paramName);

#endif
