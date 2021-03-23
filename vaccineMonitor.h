#ifndef VACCINEMONITOR_H
#define VACCINEMONITOR_H

#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"
#include "DataStructures/skipList/skipList.h"
#include "DataStructures/date/date.h"
#include "DataStructures/population/population.h"

class vaccineMonitor
{
public:
    vaccineMonitor(int bloomSize);
    ~vaccineMonitor();

    void addFromFile(string filePath);
    void addRecord(int length, string *words, string line);
    void startMenu();

private:
    void addNewVirus(string virusName);
    void addNewCountry(string countryName);
    int checkSyntaxRecord(int length, string *words, string input);
    // COMMANDS
    void vaccineStatusBloom(string *arguments, int length);
    void vaccineStatus(string *arguments, int length);
    void treeInOrderPopulationCountry(treeNode *node, population **stat, linkedListStringNode *country, linkedListStringNode *virus, date date1, date date2);
    void treeInOrderPopulationGlobal(treeNode *node, population **stat, linkedListStringNode *virus, date date1, date date2);
    void populationStatus(string *arguments, int length);
    void treeInOrderPopulationByAgeCountry(treeNode *node, population **stat, linkedListStringNode *country, linkedListStringNode *virus, date date1, date date2);
    void treeInOrderPopulationByAgeGlobal(treeNode *node, population **stat, linkedListStringNode *virus, date date1, date date2);
    void popStatusByAge(string *arguments, int length);
    void insertCitizenRecord(string line);
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