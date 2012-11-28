#include <uC++.h>
#include <iostream>
#include "MPRNG.h"
#include "q1configparams.h"
#include "q1printer.h"
#include "q1bank.h"
#include "q1parent.h"
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
  Bank bank(params.numStudents);
  Parent parent(printer, bank, params.numStudents, params.parentalDelay);

  // delete stuff
}
