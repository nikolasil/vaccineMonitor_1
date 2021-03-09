#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../../citizenRecords/citizen.h"

class skipListNode
{
public:
    skipListNode(int id);
    ~skipListNode();
    void destroy();
    void add(skipListNode **list, skipListNode *new_node);
    void remove(skipListNode **list, int key);

    void print();

    void setNext(skipListNode *temp);
    void setDown(skipListNode *temp);
    void setId(int id);
    void setCitizen();

    skipListNode *getNext();
    skipListNode *getDown();
    int getId();
    citizenRecord *getCitizen();

private:
    int coinFlip();

    int id;
    citizenRecord *citizen;
    skipListNode *next;
    skipListNode *down;
};

class skipListLevel
{
public:
    skipListLevel();
    ~skipListLevel();

    skipListNode *add(int id);

private:
    skipListNode *list;
    skipListLevel *downLevel;
};

class skipList
{
public:
    skipList();
    ~skipList();

private:
    int maxLevels;
    skipList *ceiling;
    skipList *floor;
};

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
};

#endif