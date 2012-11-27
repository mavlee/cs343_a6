#include "q1student.h"

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases) {
  this->prt = &prt;
  server = &nameServer;
  office = &cardOffice;
  this->id = id;
  this->maxPurchases = maxPurchases;
}

void Student::main() {

}