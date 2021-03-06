#include <iostream>

#include "skipList.h"

int coinFlip()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    return rand() % 2;
}

skipListNode::skipListNode(int id) : id(id)
{
}

skipListNode::~skipListNode()
{
    if (this->next != NULL)
    {
        delete this->next;
    }
}

skipList::skipList()
{
}

skipList::~skipList()
{
}

skipListNode *skipList::add(int id)
{
}