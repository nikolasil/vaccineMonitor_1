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

void skipListNode::add(skipListNode *new_node)
{
    skipListNode *curr = this;
    while (curr->next != NULL && curr->next->id < new_node->id)
    {
        curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
}

void skipListNode::remove(int key)
{
    skipListNode *temp = this;
    skipListNode *prev = NULL;

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

// skipListLevel

skipListLevel::skipListLevel(skipListLevel *prevLevel, int l) : myLevel(l)
{
    this->list = new skipListNode(NEG_INF);
    this->pos_inf = new skipListNode(POS_INF);
    this->list->setNext(this->pos_inf);

    this->list->setDown(prevLevel->getNegInf());
    this->pos_inf->setDown(prevLevel->getPosInf());

    this->downLevel = prevLevel;
    this->upLevel = NULL;
}

skipListLevel::skipListLevel() : myLevel(0)
{
    this->list = new skipListNode(NEG_INF);
    this->pos_inf = new skipListNode(POS_INF);
    this->list->setNext(this->pos_inf);

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

int skipListLevel::getMyLevel()
{
    return this->myLevel;
}

skipListNode *skipListLevel::getList()
{
    return this->list;
}

skipListNode *skipListLevel::getPosInf()
{
    return this->pos_inf;
}

skipListNode *skipListLevel::getNegInf()
{
    return this->list;
}

void skipListLevel::print()
{
    this->list->print();
}

// skipList

skipList::skipList()
{
    this->floor = new skipListLevel();
    this->ceiling = this->floor;
}

skipList::~skipList()
{
    skipListLevel *temp = this->ceiling;
    while (temp != NULL)
    {
        temp->getList()->destroy();
        skipListLevel *next = temp->getDownLevel();
        delete temp;
        temp = next;
    }
}

void skipList::add(int id)
{
    skipListLevel *currLevel = this->ceiling;
    skipListNode *currNode = ceiling->getNegInf();
    skipListNode *nextNode = currNode->getNext();

    skipListNode *prevCreated = NULL;
    int create = 0;
    while (1)
    {
        if (id < nextNode->getId())
        {
            if (currNode->coinFlip() || create)
            { // create a node
                if (create)
                {
                    skipListNode *downNode = new skipListNode(id);
                    prevCreated->setDown(downNode);
                    currNode->setNext(downNode);
                    downNode->setNext(nextNode);
                    prevCreated = downNode;
                }
                else if (!create) // if it is the first time
                {
                    prevCreated = new skipListNode(id);
                    currNode->setNext(prevCreated);
                    prevCreated->setNext(nextNode);
                    if (prevCreated->coinFlip() && currLevel == this->ceiling && this->ceiling->getMyLevel() < maxLevels - 1)
                    { // make a new level
                        skipListLevel *newLevel = new skipListLevel(this->ceiling, this->ceiling->getMyLevel() + 1);
                        this->ceiling->setUpLevel(newLevel);
                        this->ceiling = newLevel;
                        this->ceiling->getList()->add(new skipListNode(prevCreated));
                    }
                    create = 1;
                }
            }

            if (currNode->getDown() != NULL)
            { // if there is a down level
                // step down
                currNode = currNode->getDown();
                nextNode = currNode->getNext();
                currLevel = currLevel->getDownLevel();
            }
            else
            {
                if (!create)
                {
                    prevCreated = new skipListNode(id);
                    currNode->setNext(prevCreated);
                    prevCreated->setNext(nextNode);
                }
                return;
            }
        }
        else if (id > nextNode->getId())
        {
            currNode = nextNode;
            nextNode = nextNode->getNext();
        }
        else
        {
            return;
        }
    }
}

void skipList::remove(int id)
{
}

void skipList::search(int id)
{
}

skipListLevel *skipList::getCeiling()
{
    return this->ceiling;
}

skipListLevel *skipList::getFloor()
{
    return this->floor;
}

void skipList::print()
{
    skipListLevel *temp = this->ceiling;
    while (temp != NULL)
    {
        temp->print();
        temp = temp->getDownLevel();
    }
}