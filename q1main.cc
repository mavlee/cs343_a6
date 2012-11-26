#include <uC++.h>
#include <iostream>
#include "MPRNG.h"
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

  // set the seed
  rng.seed(seed);

  // init stuff

  // delete stuff
}
