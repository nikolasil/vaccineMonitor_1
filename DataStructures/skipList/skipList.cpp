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

// void skipListNode::add(skipListNode **list, skipListNode *new_node)
// {
//     skipListNode *curr;
//     if (*list == NULL || (*list)->id >= new_node->id)
//     {
//         new_node->next = *list;
//         *list = new_node;
//     }
//     else
//     {
//         curr = *list;
//         while (curr->next != NULL && curr->next->id < new_node->id)
//         {
//             curr = curr->next;
//         }
//         new_node->next = curr->next;
//         curr->next = new_node;
//     }
// }

// void skipListNode::remove(skipListNode **list, int key)
// {
//     skipListNode *temp = *list;
//     skipListNode *prev = NULL;

//     if (temp != NULL && temp->id == key)
//     {
//         *list = temp->next;
//         delete temp;
//         return;
//     }
//     else
//     {
//         while (temp != NULL && temp->id != key)
//         {
//             prev = temp;
//             temp = temp->next;
//         }

//         if (temp == NULL)
//             return;
//         prev->next = temp->next;
//         delete temp;
//     }
// }

// skipListLevel

skipListLevel::skipListLevel(skipListLevel *prevLevel, int l) : myLevel(l)
{
    this->list = new skipListNode(NEG_INF);
    this->pos_inf = new skipListNode(POS_INF);
    this->list->add(&this->list, this->pos_inf);

    this->list->setDownLevel(prevLevel->getNegInf());
    this->pos_inf->setDownLevel(prevLevel->getPosInf());

    this->downLevel = NULL;
    this->upLevel = NULL;
}

skipListLevel::skipListLevel() : myLevel(0)
{
    this->list = new skipListNode(NEG_INF);
    this->pos_inf = new skipListNode(POS_INF);
    this->list->add(&this->list, this->pos_inf);

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
}

void skipList::add(int id)
{
    skipListLevel *currNode = ceiling->getPosInf();
    skipListLevel *nextNode = currNode->getNext();

    skipListNode *newNode = new skipListNode(id);

    while (1)
    {
        if (id < nextNode->getId())
        {
            // step down

            if (currNode->getDownLevel() != NULL)
            { // IF THERE IS A DOWN LEVEL
                currNode = currNode->getDownLevel();
                nextNode = currNode->getNext();
                continue;
            }
            else
            { /* if there is no down
                we will put the new node after the currNode*/
                currNode->setNext(newNode);
                newNode->setNext(nextNode);
                // TODO: flip a coin
                return;
            }
        }
        else
        {
        }
    }
}

void skipList::remove(int id)
{
}

void skipList::search(int id)
{
}

skipListLevel *getCeiling();
{
    return this->ceiling;
}

skipListLevel *getFloor()
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