#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <limits>
#include "../../citizenRecords/citizen.h"
#include "../linkedList/linkedListString.h"

#define POS_INF std ::numeric_limits<int>::max()
#define NEG_INF std ::numeric_limits<int>::min()
#define maxLevels 9

class skipListNode
{
public:
    skipListNode(int id, citizenRecord *citizen);
    skipListNode(skipListNode *node);
    ~skipListNode();
    void destroy();

    void add(skipListNode *new_node);

    // GETTERS
    skipListNode *getNext();
    skipListNode *getDown();
    int getId();
    citizenRecord *getCitizen();

    // SETTERS
    void setNext(skipListNode *temp);
    void setDown(skipListNode *temp);
    void setId(int id);
    void setCitizen(citizenRecord *citizen);

    void print();

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

    skipListLevel *getDownLevel();
    skipListNode *getList();
    skipListNode *getPosInf();
    skipListNode *getNegInf();
    int getMyLevel();

    void setDownLevel(skipListLevel *down);
    void setList(skipListNode *l);
    void setPosInf(skipListNode *p);
    void setNegInf(skipListNode *n);
    void setMyLevel(int l);

    void print();

private:
    int myLevel;
    skipListNode *list;
    skipListNode *pos_inf;

    skipListLevel *downLevel;
};

class skipList
{
public:
    skipList();
    ~skipList();

    void add(int id, citizenRecord *citizen);
    void remove(int id);
    skipListNode *search(int id, char top_bottom);

    // GETTERS
    skipListLevel *getCeiling();
    skipListLevel *getFloor();
    // SETTERS
    void setCeiling(skipListLevel *c);
    void setFloor(skipListLevel *f);

    void print();
    int coinFlip();

private:
    skipListLevel *ceiling;
    skipListLevel *floor;
};

class skipList_Lists
{
public:
    skipList_Lists();
    skipList_Lists(linkedListStringNode *virus);
    ~skipList_Lists();

    skipList_Lists *add(linkedListStringNode *virus);

    // GETTERS
    linkedListStringNode *getVirus();
    skipList *getVaccinated(linkedListStringNode *virus);
    skipList *getVaccinated();
    skipList *getNotVaccinated(linkedListStringNode *virus);
    skipList *getNotVaccinated();
    skipList_Lists *getNext();
    // SETTERS
    void setVirus(linkedListStringNode *v);
    void setVaccinated(skipList *l, linkedListStringNode *virus);
    void setVaccinated(skipList *l);
    void setNotVaccinated(skipList *l, linkedListStringNode *virus);
    void setNotVaccinated(skipList *l);
    void setNext(skipList_Lists *n);

private:
    linkedListStringNode *virus;
    skipList *vaccinated;
    skipList *notVaccinated;
    skipList_Lists *next;
};

#endif