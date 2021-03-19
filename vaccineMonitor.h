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
    void addNewVirus(string virusName);
    void addNewCountry(string countryName);
    int checkSyntaxRecord(int length, string *words, string input);
    // COMMANDS
    void vaccineStatusBloom(string *arguments, int length);
    void vaccineStatus(string *arguments, int length);
    void populationStatus(string *arguments, int length);
    void popStatusByAge(string *arguments, int length);
    void insertCitizenRecord(string *arguments, int length);
    void vaccinateNow(string *arguments, int length);
    void listNonVaccinatedPersons(string *arguments, int length);
    void teminate();

    treeNode *tree;
    linkedListStringNode *countryList;
    linkedListStringNode *virusList;
    bloomFilterList *bloomList;
    skipList_Lists *skiplist;
};

#endif