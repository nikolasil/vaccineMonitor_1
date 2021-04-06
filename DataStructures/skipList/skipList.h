#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <limits>
#include "../../citizenRecords/citizen.h"
#include "../stringList/stringList.h"

#define POS_INF std ::numeric_limits<int>::max()
#define NEG_INF std ::numeric_limits<int>::min()
#define maxLevels 9

class skipListNode
{
public:
    skipListNode(citizenRecord* citizen);
    skipListNode(skipListNode* node);
    ~skipListNode();
    void destroy();

    void add(skipListNode* new_node);

    // GETTERS
    skipListNode* getNext();
    skipListNode* getDown();
    int getId();
    citizenRecord* getCitizen();

    // SETTERS
    void setNext(skipListNode* temp);
    void setDown(skipListNode* temp);
    void setCitizen(citizenRecord* citizen);

    void printIds();
    void printCitizens();

private:
    citizenRecord* citizen;
    skipListNode* next;
    skipListNode* down;
};

class skipListLevel
{
public:
    skipListLevel(skipListLevel* prevLevel, int l);
    skipListLevel();
    ~skipListLevel();

    skipListLevel* getDownLevel();
    skipListNode* getList();
    skipListNode* getPosInf();
    skipListNode* getNegInf();
    int getMyLevel();

    void setDownLevel(skipListLevel* down);
    void setList(skipListNode* l);
    void setPosInf(skipListNode* p);
    void setNegInf(skipListNode* n);
    void setMyLevel(int l);

    void printIds();
    void printCitizens();

private:
    int myLevel;
    skipListNode* list;
    skipListNode* pos_inf;
    skipListLevel* downLevel;
};

class skipList
{
public:
    skipList();
    ~skipList();

    void add(int id, citizenRecord* citizen);
    void remove(int id);
    skipListNode* search(int id, char top_bottom);

    // GETTERS
    skipListLevel* getCeiling();
    skipListLevel* getFloor();
    // SETTERS
    void setCeiling(skipListLevel* c);
    void setFloor(skipListLevel* f);
    bool isEmpty();
    void printIds();
    void printFloor();
    int coinFlip();

private:
    skipListLevel* ceiling;
    skipListLevel* floor;
};

class skipList_Lists
{
public:
    skipList_Lists();
    skipList_Lists(stringList* virus);
    ~skipList_Lists();

    skipList_Lists* add(stringList* virus);

    // GETTERS
    stringList* getVirus();
    skipList* getVaccinated(stringList* virus);
    skipList* getVaccinated();
    skipList* getNotVaccinated(stringList* virus);
    skipList* getNotVaccinated();
    skipList_Lists* getNext();
    // SETTERS
    void setVirus(stringList* v);
    void setVaccinated(skipList* l, stringList* virus);
    void setVaccinated(skipList* l);
    void setNotVaccinated(skipList* l, stringList* virus);
    void setNotVaccinated(skipList* l);
    void setNext(skipList_Lists* n);

private:
    stringList* virus;
    skipList* vaccinated;
    skipList* notVaccinated;
    skipList_Lists* next;
};

#endif