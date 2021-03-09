#include <iostream>

#include "skipList.h"
#include "../../citizenRecords/citizen.h"

int skipListNode::coinFlip()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    return rand() % 2;
}

skipListNode::skipListNode(int id) : id(id)
{
    this->next = NULL;
    this->down = NULL;
}

skipListNode::~skipListNode()
{
}

void skipListNode::destroy()
{
    skipListNode *temp = this->next;
    if (this != NULL)
    {
        while (temp != NULL)
        {
            skipListNode *next = temp->next;
            delete temp;
            temp = next;
        }
        delete this;
    }
}

void skipListNode::print()
{
    skipListNode *temp = this;
    while (temp != NULL)
    {
        cout << temp->id << " ";
        temp = temp->next;
    }
    cout << endl;
}

void skipListNode::setNext(skipListNode *temp)
{
    this->next = temp;
}

void skipListNode::setDown(skipListNode *temp)
{
    this->down = temp;
}

void skipListNode::setId(int id)
{
    this->id = id;
}

void skipListNode::setCitizen()
{
}

skipListNode *skipListNode::getNext()
{
    return this->next;
}

skipListNode *skipListNode::getDown()
{
    return this->down;
}

int skipListNode::getId()
{
    return this->id;
}

citizenRecord *skipListNode::getCitizen()
{
    return this->citizen;
}

void skipListNode::add(skipListNode **list, skipListNode *new_node)
{
    skipListNode *curr;
    if (*list == NULL || (*list)->id >= new_node->id)
    {
        new_node->next = *list;
        *list = new_node;
    }
    else
    {
        curr = *list;
        while (curr->next != NULL && curr->next->id < new_node->id)
        {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }
}

void skipListNode::remove(skipListNode **list, int key)
{
    skipListNode *temp = *list;
    skipListNode *prev = NULL;

    if (temp != NULL && temp->id == key)
    {
        *list = temp->next;
        delete temp;
        return;
    }
    else
    {
        while (temp != NULL && temp->id != key)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;
        prev->next = temp->next;
        delete temp;
    }
}