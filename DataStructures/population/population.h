/*
    This file contains the population class that is used
    in the /populationStatus and /popStatusByAge commands
    to make all th statistics needed.
*/

#ifndef POPULATION_H
#define POPULATION_H

#include <string>
#include "../stringList/stringList.h"

using namespace std;

class yes
{
public:
    yes(unsigned int y);
    ~yes();

    unsigned int y;
    yes* next;
};

class no
{
public:
    no(unsigned int n);
    ~no();

    unsigned int n;
    no* next;
};

class noneInfo
{
public:
    noneInfo(unsigned int x);
    ~noneInfo();

    unsigned int noInfo;
    noneInfo* next;
};

class population
{
public:
    population(stringList* c, bool byAge);
    ~population();

    void print();

    population* find(stringList* country);

    void inYes(int pos);  // +1 to yes
    void outYes(int pos); // +1 to yes
    void NO(int pos);     // +1 to no
    void noInfo(int pos); // +1 to noInfo

    unsigned int getInYes(int pos);
    unsigned int getOutYes(int pos);
    unsigned int getNO(int pos);
    unsigned int getNoInfo(int pos);

    // GETTERS
    population* getNext() { return this->next; }
    stringList* getCountryName() { return this->countryName; }

    // SETTERS
    void setNext(population* n) { this->next = n; }

private:
    stringList* countryName; // key
    yes* inRange;
    yes* outRange;
    no* No;
    noneInfo* noInformation;
    population* next;
};

#endif