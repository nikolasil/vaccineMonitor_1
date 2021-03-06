#ifndef UTIL_H
#define UTIL_H

#include <string>

#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"

using namespace std;

string getInput(string prompt);
string *splitString(string input, int *length);

void vaccineStatusBloom(string *arguments, treeNode *tree, linkedListStringNode *virusList, bloomFilterList *bloomList);
void vaccineStatus(string *arguments);
void populationStatus(string *arguments);
void popStatusByAge(string *arguments);
void insertCitizenRecord(string *arguments);
void vaccinateNow(string *arguments);
void listNonVaccinatedPersons(string *arguments);
void teminate();

#endif