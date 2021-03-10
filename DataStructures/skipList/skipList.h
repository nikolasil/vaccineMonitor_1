#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "../../citizenRecords/citizen.h"

class skipListNode
{
public:
    skipListNode(int id);
    skipListNode(skipListNode *node);
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

    int coinFlip();

private:
    int id;
    citizenRecord *citizen;
    skipListNode *down;
    skipListNode *next;
};

class skipListLevel
{
public:
    skipListLevel(int l);
    skipListLevel();
    ~skipListLevel();

    void add(int id);

    void setUpLevel(skipListLevel *up);
    void setDownLevel(skipListLevel *down);

    skipListLevel *getUpLevel();
    skipListLevel *getDownLevel();
    skipListNode *getList();

    void print();

private:
    int myLevel;
    skipListNode *list;
    skipListLevel *upLevel;
    skipListLevel *downLevel;
};

class skipList
{
public:
    skipList();
    ~skipList();

private:
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