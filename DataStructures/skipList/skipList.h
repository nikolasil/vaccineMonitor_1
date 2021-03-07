#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../../citizenRecords/citizen.h"

class skipListNode
{
public:
    skipListNode(int id);
    ~skipListNode();

private:
    int coinFlip();

    int id;
    citizenRecord *citizen;
    skipListNode *down;
    skipListNode *next;
}

class skipList
{
public:
    skipList();
    ~skipList();

    skipListNode *add(int id);

private:
    int height;
    skipListNode *list;
    skipList *upLevel;
    skipList *downLevel;
}

class skipList_Lists
{
public:
    skipList_Lists();
    ~skipList_Lists();

private:
    string virus;
    skipList *vaccinated;
    skipList *notVaccinated;
    skipList_Lists *nextSkipList;
}

#endif