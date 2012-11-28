#include <uC++.h>
#include <iostream>
#include "MPRNG.h"
#include "q1configparams.h"
#include "q1printer.h"
#include "q1bank.h"
#include "q1parent.h"
#include "q1watcardoffice.h"
#include "q1watcard.h"
#include "q1nameserver.h"
#include "q1bottlingplant.h"
#include "q1student.h"
#include "q1truck.h"
#include "q1vendingmachine.h"
using namespace std;

// global random number generator
MPRNG rng;

/********* usage ************
 * Purpose: gives out an error message when input is incorrect
 * Returns: void
 * Arugments: avgv[] - the arguments passed into the program
 ***************************/
void usage(char *argv[]) {
  cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]" << endl;
  exit(EXIT_FAILURE);
}

/********* main ************
 * Purpose: takes in input and creates the soda distribution chain
 * Returns: void
 ***************************/
void uMain::main() {
  // set the defaults first
  string configFile = "soda.config";
  int seed = (int) getpid();
  ifstream file;
  ConfigParams params;

  // for usage in loops
  unsigned int i;

  // read in command line arguments
  if (argc > 1)
    configFile = atoi(argv[1]);
  if (argc > 2)
    seed = atoi(argv[2]);
  if (argc > 3) usage(argv);

  // invalid seed argument
  if (seed < 1)
    usage(argv);

  // try to read in the file
  try {
    file.open(configFile.c_str());
    processConfigFile(configFile.c_str(), params);
  } catch (uFile::Failure) {
    cerr << "Error: could not open input file " << configFile << endl;
    exit(EXIT_FAILURE);
  }

  // set the seed
  rng.seed(seed);

  // init stuff
  // It then creates in
  // order the printer, bank, parent, WATCard ofﬁce, name server, vending machines, bottling plant, and students. The
  // truck is created by the bottling plant; the couriers are created by the WATCard ofﬁce.
  Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
  Bank *bank = new Bank(params.numStudents);
  Parent *parent = new Parent(printer, *bank, params.numStudents, params.parentalDelay);
  WATCardOffice *office = new WATCardOffice(printer, *bank, params.numCouriers);
  NameServer *nameServer = new NameServer(printer, params.numVendingMachines, params.numStudents);
  BottlingPlant *bottlingPlant = new BottlingPlant(printer, *nameServer, params.numVendingMachines, params.maxShippedPerFlavour, params.maxStockPerFlavour, params.timeBetweenShipments);
  Student *students[params.numStudents];
  VendingMachine *machines[params.numVendingMachines];
  for (i = 0; i < params.numStudents; i++)
    students[i] = new Student(printer, *nameServer, *office, i, params.maxPurchases);

  for (i = 0; i < params.numVendingMachines; i++)
    machines[i] = new VendingMachine(printer, *nameServer, i, params.sodaCost, params.maxStockPerFlavour);

  for (i = 0; i < params.numStudents; i++)
    delete students[i];

  for (i = 0; i < params.numVendingMachines; i++)
    delete machines[i];

  // delete stuff other
}
