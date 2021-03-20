#ifndef VACCINEMONITOR_H
#define VACCINEMONITOR_H

#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"
#include "DataStructures/skipList/skipList.h"
#include "DataStructures/date/date.h"

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
    void treeInOrderPopulationGlobal(treeNode *tree);
    void treeInOrderPopulationCountry(treeNode *tree, population **stat, linkedListStringNode *country, linkedListStringNode *virus, date date1, date date2);
    void populationStatus(string *arguments, int length);
    void treeInOrderPopulationByAge(treeNode *tree, int length);
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