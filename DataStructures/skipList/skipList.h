#ifndef SKIPLIST_H
#define SKIPLIST_H

class skipListNode
{
public:
    skipListNode(int id);
    ~skipListNode();

private:
    int id;
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
    skipList *nextLevel;
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