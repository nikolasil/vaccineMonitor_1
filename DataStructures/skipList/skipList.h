#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <limits>
#include "../../citizenRecords/citizen.h"

#define POS_INF std ::numeric_limits<int>::max()
#define NEG_INF std ::numeric_limits<int>::min()
#define maxLevels 9

class skipListNode
{
public:
    skipListNode(int id);
    skipListNode(skipListNode *node);
    ~skipListNode();
    void destroy();

    void add(skipListNode *new_node);
    void remove(int key);

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
    skipListLevel(skipListLevel *prevLevel, int l);
    skipListLevel();
    ~skipListLevel();

    void setUpLevel(skipListLevel *up);
    void setDownLevel(skipListLevel *down);

    skipListLevel *getUpLevel();
    skipListLevel *getDownLevel();
    int getMyLevel();
    skipListNode *getList();
    skipListNode *getPosInf();
    skipListNode *getNegInf();

    void print();

private:
    int myLevel;
    skipListNode *list;
    skipListNode *pos_inf;
    skipListLevel *upLevel;
    skipListLevel *downLevel;
};

class skipList
{
public:
    skipList();
    ~skipList();

    void add(int id);
    void remove(int id);
    void search(int id);

    void print();

    skipListLevel *getCeiling();
    skipListLevel *getFloor();

private:
    skipListLevel *ceiling;
    skipListLevel *floor;
};

// class skipList_Lists
// {
// public:
//     skipList_Lists();
//     ~skipList_Lists();

// private:
//     string virus;
//     skipList *vaccinated;
//     skipList *notVaccinated;
//     skipList_Lists *nextSkipList;
// };

#endif