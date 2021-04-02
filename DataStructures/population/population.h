#ifndef POPULATION_H
#define POPULATION_H

#include <string>
#include "../linkedList/linkedListString.h"

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
    population(linkedListStringNode* c, bool byAge);
    ~population();

    population* find(linkedListStringNode* country);

    void inYes(int pos);  // +1 to yes
    void outYes(int pos); // +1 to yes
    void NO(int pos);     // +1 to no
    void noInfo(int pos); // +1 to noInfo

    // SETTERS
    void setNext(population* n);

    // GETTERS
    population* getNext();
    linkedListStringNode* getCountryName();
    unsigned int getInYes(int pos);
    unsigned int getOutYes(int pos);
    unsigned int getNO(int pos);
    unsigned int getNoInfo(int pos);

    void print();

private:
    linkedListStringNode* countryName; // key
    yes* inRange;
    yes* outRange;
    no* No;
    noneInfo* noInformation;
    population* next;
};

#endif