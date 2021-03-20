#ifndef POPULATION_H
#define POPULATION_H

#include <string>

using namespace std;

class yes_no
{
public:
    yes_no(unsigned int y, unsigned int n);
    ~yes_no();

    unsigned int yes;
    unsigned int no;
    yes_no *next;
}

class populationCountry
{
public:
    populationCountry(linkedListStringNode *c, bool byAge);
    ~populationCountry();

    void inYes(int pos);  // +1 to yes
    void inNo(int pos);   // +1 to no
    void outYes(int pos); // +1 to yes
    void outNo(int pos);  // +1 to no        // +1 to no

    // SETTERS
    void setNext(populationCountry *n);

    // GETTERS
    populationCountry *getNext();
    linkedListStringNode *getCountryName();
    unsigned int getInYes(int pos);
    unsigned int getInNo(int pos);
    unsigned int getOutYes(int pos);
    unsigned int getOutNo(int pos);

    void print();

private:
    linkedListStringNode *countryName; // key
    yes_no *inRange;
    yes_no *outRange;
    populationCountry *next;
};

#endif