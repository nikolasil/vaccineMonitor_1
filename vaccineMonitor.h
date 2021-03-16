#ifndef VACCINEMONITOR_H
#define VACCINEMONITOR_H

#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"
#include "DataStructures/skipList/skipList.h"

class vaccineMonitor
{
public:
    vaccineMonitor(int bloomSize);
    ~vaccineMonitor();

    void addFromFile(string filePath);
    void addRecord(string input);

    void startMenu();

private:
    // COMMANDS
    void vaccineStatusBloom(string *arguments, treeNode *tree, linkedListStringNode *virusList, bloomFilterList *bloomList);
    void vaccineStatus(string *arguments);
    void populationStatus(string *arguments);
    void popStatusByAge(string *arguments);
    void insertCitizenRecord(string *arguments);
    void vaccinateNow(string *arguments);
    void listNonVaccinatedPersons(string *arguments);
    void teminate();

    treeNode *tree;
    linkedListStringNode *countryList;
    linkedListStringNode *virusList;
    bloomFilterList *bloomList;
    skipList_Lists *skiplist;
};

#endif