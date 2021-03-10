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
    this->citizen = NULL;
}

skipListNode::skipListNode(skipListNode *node)
{
    this->id = node->getId();
    this->citizen = node->getCitizen();
    this->next = NULL;
    this->down = node;
}

skipListNode::~skipListNode()
{
}

void skipListNode::destroy()
{
    if (this != NULL)
    {
        skipListNode *temp = this->next;
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
        // cout << "[" << temp->id << "," << temp << "," << temp->down << "]";
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

// skipListLevel

skipListLevel::skipListLevel(int l) : myLevel(l)
{
    this->list = NULL;
    this->downLevel = NULL;
    this->upLevel = NULL;
}

skipListLevel::skipListLevel() : myLevel(0)
{
    this->list = NULL;
    this->downLevel = NULL;
    this->upLevel = NULL;
}

skipListLevel::~skipListLevel()
{
}

void skipListLevel::setUpLevel(skipListLevel *up)
{
    this->upLevel = up;
}

void skipListLevel::setDownLevel(skipListLevel *down)
{
    this->downLevel = down;
}

skipListLevel *skipListLevel::getUpLevel()
{
    return this->upLevel;
}

skipListLevel *skipListLevel::getDownLevel()
{
    return this->downLevel;
}

skipListNode *skipListLevel::getList()
{
    return this->list;
}

void skipListLevel::print()
{
    this->list->print();
}

void skipListLevel::add(int id)
{
    skipListNode *new_node = new skipListNode(id);
    if (this->list == NULL)
    {
        this->list = new_node;
    }
    else
    {
        this->list->add(&this->list, new_node);
    }
    skipListNode *temp = new_node;
    skipListLevel *level = this;
    while (temp->coinFlip())
    {
        if (level->myLevel != 9)
        {
            skipListNode *up_node = new skipListNode(temp);
            if (level->upLevel == NULL)
            {
                level->upLevel = new skipListLevel(level->myLevel + 1);
                level->upLevel->setDownLevel(level);
                level->upLevel->list = up_node;
            }
            else
            {
                level->upLevel->list->add(&level->upLevel->list, up_node);
            }

            level = level->upLevel;
            temp = up_node;
        }
        else
        {
            break;
        }
    }
}