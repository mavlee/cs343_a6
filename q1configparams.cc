#include "q1configparams.h"
#include <iostream>

using namespace std;

bool matchParameter(string line, string paramName) {
    return line.find(paramName) != string::npos;
}

void processConfigFile(const char *configFile, ConfigParams &cparams) {
    ifstream file;
    bool isComment = false;
    try {
        file.open(configFile);
    } catch (uFile::Failure) {
        cerr << "Error: could not open input file" << endl;
        return;
    }
    string line;
    while (file >>line) {
        if (!isComment) {
            if (matchParameter(line, "SodaCost")) {
                file >> line;
                cparams.sodaCost = atoi(line.c_str());
            } else if (matchParameter(line, "NumStudents")) {
                file >> line;
                cparams.numStudents = atoi(line.c_str());
            } else if (matchParameter(line, "MaxPurchases")) {
                file >> line;
                cparams.maxPurchases = atoi(line.c_str());
            } else if (matchParameter(line, "NumVendingMachines")) {
                file >> line;
                cparams.numVendingMachines = atoi(line.c_str());
            } else if (matchParameter(line, "MaxStockPerFlavour")) {
                file >> line;
                cparams.maxStockPerFlavour = atoi(line.c_str());
            } else if (matchParameter(line, "MaxShippedPerFlavour")) {
                file >> line;
                cparams.maxShippedPerFlavour = atoi(line.c_str());
            } else if (matchParameter(line, "TimeBetweenShipments")) {
                file >> line;
                cparams.timeBetweenShipments = atoi(line.c_str());
            } else if (matchParameter(line, "ParentalDelay")) {
                file >> line;
                cparams.parentalDelay = atoi(line.c_str());
            } else if (matchParameter(line, "NumCouriers")) {
                file >> line;
                cparams.numCouriers = atoi(line.c_str());
            } else if (matchParameter(line, "#")) {
                isComment = true;
            }
        } else {
            if (file.peek() == '\n')
                isComment = false;
        }
    }
}