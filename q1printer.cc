#include <uC++.h>
#include "q1printer.h"
#include <iostream>

/********* Printer ************
 * Purpose: creates the printer and print the header
 * Returns: void
 * Arguments: numStudents - the number of students
 *            numVendingMachines - number of vending machines
 *            numCouriers - the number of couriers
 ***************************/
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) {
  this->numStudents = numStudents;
  this->numVendingMachines = numVendingMachines;
  this->numCouriers = numCouriers;
  numObjects = numStudents + numVendingMachines + numCouriers + 5;
  unsigned int i;   // for use in loops

  status = new char[numObjects];
  // init all the statuses to null char
  for (unsigned int i = 0; i < numObjects; i++)
    status[i] = '\0';

  statusNumbers = new int *[numObjects];
  for (unsigned int i = 0; i < numObjects; i++) {
    statusNumbers[i] = new int[2];
    statusNumbers[i][0] = -1;
    statusNumbers[i][1] = -1;
  }

  // print the table header
  printf("Parent\tWATOff\tNames\tTruck\tPlant\t");
  for (i = 0; i < numStudents; i++)
    printf("Stud%d\t", i);
  for (i = 0; i < numVendingMachines; i++)
    printf("Mach%d\t", i);
  for (i = 0; i < numCouriers; i++)
    printf("Cour%d\t", i);
  printf("\n");
  for (i = 0; i < numObjects; i++)
    printf("*******\t");
  printf("\n");
}

/********* print ************
 * Purpose: stores state for an object
 * Returns: void
 * Arguments: kind - the type of object
 *            state - the state of the object
 ***************************/
void Printer::print( Kind kind, char state ) {
  // call another version of print to avoid redundant code
  print(kind, state, 0, 0);

  // special case for finishing - only happens in this value-free case
  if (state == 'F')
    printFinish();
}

/********* print ************
 * Purpose: stores state for a voter
 * Returns: void
 * Arguments: kind - the type of object
 *            state - the state of the object
 *            value1 - the status value
 ***************************/
void Printer::print( Kind kind, char state, int value1 ) {
  // call another version of print to avoid redundant code
  print(kind, state, value1, 0);
}

/********* print ************
 * Purpose: stores state for a voter
 * Returns: void
 * Arguments: kind - the type of object
 *            state - the state of the object
 *            value1 - the first status value
 *            value2 - the second status value
 ***************************/
void Printer::print( Kind kind, char state, int value1, int value2 ) {
  // if state is already there, print before storing
  if (status[kind] != '\0')
    displayStatus();
  status[kind] = state;
  statusValues[kind][0] = value1;
  statusValues[kind][1] = value2;
}

/********* print ************
 * Purpose: stores state for an object
 * Returns: void
 * Arguments: kind - the type of object
 *            lid - the id of the object
 *            state - the state of the object
 ***************************/
void Printer::print( Kind kind, unsigned int lid, char state ) {
  // call another version of print to avoid redundant code
  print(kind, lid, state, 0, 0);

  // special case for finishing - only happens in this value-free case
  if (state == 'F')
    printFinish();
}

/********* print ************
 * Purpose: stores state for a voter
 * Returns: void
 * Arguments: kind - the type of object
 *            lid - the id of the object
 *            state - the state of the object
 *            value1 - the status value
 ***************************/
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
  // call another version of print to avoid redundant code
  print(kind, lid, state, value1, 0);
}

/********* print ************
 * Purpose: stores state for a voter
 * Returns: void
 * Arguments: kind - the type of object
 *            lid - the id of the object
 *            state - the state of the object
 *            value1 - the first status value
 *            value2 - the second status value
 ***************************/
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
  unsigned int id = 5;
  if (kind == Student)
    id += lid;
  else if (kind == Vending)
    id += numStudents + lid;
  else if (kind == Courier)
    id += numStudents + numVendingMachines + lid;
  // if state is already there, print before storing
  if (status[id] != '\0')
    displayStatus();
  status[id] = state;
  statusValues[id][0] = value1;
  statusValues[id][1] = value2;
}

/********* displayStatus ************
 * Purpose: prints the current state of the objects
 * Returns: void
 ***************************/
void Printer::displayStatus() {
  // fill out later

  for (unsigned int i = 0; i < numObjects; i++) {
    if (status[i] == '\0')
      printf("\t");
    else if (statusValues[i][0] >= 0 && statusValues[i][1] >= 0)
      printf("%c%d,%d\t", status[i], statusValues[i][0], statusValues[i][1]);
    else if (statusValues[i][0] >= 0)
      printf("%c%d\t", status[i], statusValues[i][0]);
    else
      printf("%c\t", status[i]);
  }
  printf("\n");

  // reset all the statuses
  for (unsigned int i = 0; i < numObjects; i++) {
    status[i] = '\0';
    statusValues[i][0] = 0;
    statusValues[i][1] = 0;
  }
}

/********* printFinish ************
 * Purpose: printing when one of the objects has finished
 * Returns: void
 ***************************/
void Printer::printFinish() {
  for (unsigned int i = 0; i < numObjects; i++) {
    // replace with "finished"
    if (status[i] == 'F') {
      printf("F\t");
      status[i] = '\0';
    } else {
      printf("...\t");
    }
  }
  printf("\n");
}

/********* destructor ************
 * Purpose: cleanup of the printer, print end message
 * Returns: void
 ***************************/
Printer::~Printer() {
  printf("***********************\n");
  delete status;
  for (unsigned int i = 0; i < numObjects; i++)
    delete [] statusNumbers[i];
  delete [] statusNumbers;
}
