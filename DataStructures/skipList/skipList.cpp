#include <iostream>

#include "skipList.h"
#include "../../citizenRecords/citizen.h"
#include "../linkedList/linkedListString.h"

using namespace std;

skipListNode::skipListNode(int id, citizenRecord *citizen) : id(id), citizen(citizen)
{
    this->setNext(NULL);
    this->setDown(NULL);
}

skipListNode::skipListNode(skipListNode *node)
{
    this->setId(node->getId());
    this->setCitizen(node->getCitizen());
    this->setNext(NULL);
    this->setDown(node);
}

skipListNode::~skipListNode()
{
}

void skipListNode::destroy()
{
    if (this != NULL)
    {
        skipListNode *temp = this->getNext();
        while (temp != NULL)
        {
            skipListNode *next = temp->getNext();
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
        cout << temp->getId() << " ";
        temp = temp->getNext();
    }
    cout << endl;
}
// GETTERS
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

// SETTERS
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

void skipListNode::setCitizen(citizenRecord *citizen)
{
    this->citizen = citizen;
}

// -- skipListLevel methods implemantation --

skipListLevel::skipListLevel(skipListLevel *prevLevel, int l) : myLevel(l)
/* when we make a new level we must make the negative and positive infinity points
to the down levels negative and positive infinity  */
{
    this->setList(new skipListNode(NEG_INF, NULL));
    this->setPosInf(new skipListNode(POS_INF, NULL));
    this->getList()->setNext(this->getPosInf());

    this->getList()->setDown(prevLevel->getNegInf());
    this->getPosInf()->setDown(prevLevel->getPosInf());

    this->setDownLevel(prevLevel);
}

skipListLevel::skipListLevel() : myLevel(0) /* this costructor in beeing called only for the 0 level */
{
    this->setList(new skipListNode(NEG_INF, NULL));
    this->setPosInf(new skipListNode(POS_INF, NULL));
    this->getList()->setNext(this->getPosInf());

    this->setDownLevel(NULL);
}

skipListLevel::~skipListLevel()
{
}

// GETTERS
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

// SETTERS
void skipListLevel::setDownLevel(skipListLevel *down)
{
    this->downLevel = down;
}

void skipListLevel::setList(skipListNode *l)
{
    this->list = l;
}

void skipListLevel::setPosInf(skipListNode *p)
{
    this->pos_inf = p;
}

void skipListLevel::setNegInf(skipListNode *n)
{
    this->list = n;
}

void skipListLevel::setMyLevel(int l)
{
    this->myLevel = l;
}

void skipListLevel::print() /* print only the list of the level */
{
    this->getList()->print();
}

// skipList methods implemantation

int skipList::coinFlip() /* returns 0 or 1 with 50% change each */
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec); // tv_nsec to change the value with nanoseconds so the function dont return the same thing every time

    return rand() % 2;
}

skipList::skipList() /* create the skip list with level 0 that has negative infinity
                        and posotive infinty nodes */
{
    this->setFloor(new skipListLevel());
    this->setCeiling(this->floor);
}

skipList::~skipList() /* delete the all the skip list levels and nodes */
{
    skipListLevel *temp = this->getCeiling();
    while (temp != NULL)
    {
        temp->getList()->destroy();
        skipListLevel *next = temp->getDownLevel();
        delete temp;
        temp = next;
    }
}

void skipList::add(int id, citizenRecord *citizen) /* add the id in the skip list
                            if it is the same id no insertion will happen*/
{
    skipListLevel *currLevel = this->getCeiling();
    skipListNode *currNode = currLevel->getNegInf();
    skipListNode *nextNode = currNode->getNext();

    skipListNode *prevCreated = NULL;
    int create = 0;
    int heightOfNewNode = 0;
    while (this->coinFlip() && (this->getCeiling()->getMyLevel() >= heightOfNewNode) && this->getCeiling()->getMyLevel() < maxLevels - 1)
    {
        heightOfNewNode++;
    }

    while (1)
    {
        if (id < nextNode->getId())
        {
            if (currLevel->getMyLevel() <= heightOfNewNode)
            { // create a node
                if (create)
                {
                    skipListNode *downNode = new skipListNode(id, citizen);
                    prevCreated->setDown(downNode);
                    currNode->setNext(downNode);
                    downNode->setNext(nextNode);
                    prevCreated = downNode;
                }
                else if (!create) // if it is the first time
                {
                    prevCreated = new skipListNode(id, citizen);
                    currNode->setNext(prevCreated);
                    prevCreated->setNext(nextNode);
                    if (currLevel == this->getCeiling() && heightOfNewNode == this->getCeiling()->getMyLevel() + 1)
                    { // make a new level
                        skipListLevel *newLevel = new skipListLevel(this->getCeiling(), this->getCeiling()->getMyLevel() + 1);
                        this->setCeiling(newLevel);
                        this->getCeiling()->getList()->add(new skipListNode(prevCreated));
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
                    prevCreated = new skipListNode(id, citizen);
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
        else if (id == nextNode->getId())
        {
            return;
        }
    }
}

void skipList::remove(int id)
{
    skipListLevel *currLevel = this->getCeiling();
    skipListNode *currNode = currLevel->getNegInf();
    skipListNode *nextNode = currNode->getNext();

    while (1)
    {
        if (id < nextNode->getId())
        {
            if (currNode->getDown() != NULL)
            { // if there is a down level
                // step down
                currNode = currNode->getDown();
                nextNode = currNode->getNext();
                currLevel = currLevel->getDownLevel();
            }
            else
            {
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
            int deleteLevel = 0;
            if (currNode == this->getCeiling()->getNegInf() && nextNode->getNext() == this->getCeiling()->getPosInf())
            {
                deleteLevel = 1;
            }
            skipListNode *toDelete = nextNode;
            currNode->setNext(nextNode->getNext());
            nextNode = toDelete->getDown();
            delete toDelete;
            if (deleteLevel && this->getCeiling() != this->getFloor())
            {
                skipListLevel *temp = this->getCeiling()->getDownLevel();
                this->getCeiling()->getList()->destroy();
                delete this->getCeiling();
                this->setCeiling(temp);
            }
            if (nextNode != NULL)
            {
                currNode = currNode->getDown();
                while (1)
                {
                    if (currNode->getNext() == nextNode)
                    {
                        break;
                    }
                    currNode = currNode->getNext();
                }
                currLevel = currLevel->getDownLevel();
            }
            else
            {
                return;
            }
        }
    }
}

skipListNode *skipList::search(int id, char top_bottom = 't')
{
    skipListLevel *currLevel = this->getCeiling();
    skipListNode *currNode = currLevel->getNegInf();
    skipListNode *nextNode = currNode->getNext();

    while (1)
    {
        if (id < nextNode->getId())
        {
            if (currNode->getDown() != NULL)
            { // if there is a down level
                // step down
                currNode = currNode->getDown();
                nextNode = currNode->getNext();
                currLevel = currLevel->getDownLevel();
            }
            else
            {
                return NULL;
            }
        }
        else if (id > nextNode->getId())
        {
            currNode = nextNode;
            nextNode = nextNode->getNext();
        }
        else
        {
            if (top_bottom == 'b')
            {
                while (1)
                {
                    if (nextNode->getDown() == NULL)
                    {
                        break;
                    }
                    nextNode = nextNode->getDown();
                }
            }
            return nextNode;
        }
    }
}

// GETTERS
skipListLevel *skipList::getCeiling()
{
    return this->ceiling;
}

skipListLevel *skipList::getFloor()
{
    return this->floor;
}

// SETTERS
void skipList::setCeiling(skipListLevel *c)
{
    this->ceiling = c;
}
void skipList::setFloor(skipListLevel *f)
{
    this->floor = f;
}

void skipList::print() /* print all the levels one by one */
{
    skipListLevel *temp = this->getCeiling();
    while (temp != NULL)
    {
        temp->print();
        temp = temp->getDownLevel();
    }
}

// skipList methods implemantation

skipList_Lists::skipList_Lists()
{
    this->setVirus(NULL);
    this->setVaccinated(NULL);
    this->setNotVaccinated(NULL);
    this->setNext(NULL);
}

skipList_Lists::skipList_Lists(linkedListStringNode *virus)
{
    this->setVirus(virus);
    this->setVaccinated(new skipList());
    this->setNotVaccinated(new skipList());
    this->setNext(NULL);
}

skipList_Lists::~skipList_Lists()
{
    if (this->getVaccinated() != NULL)
    {
        delete this->getVaccinated();
    }
    if (this->getNotVaccinated() != NULL)
    {
        delete this->getNotVaccinated();
    }
    if (this->getNext() != NULL)
    {
        delete this->getNext();
    }
}

skipList_Lists *skipList_Lists::add(linkedListStringNode *virus)
{
    if (this->getVirus() == NULL)
    {
        this->setVirus(virus);
        this->setVaccinated(new skipList());
        this->setNotVaccinated(new skipList());
        return this;
    }
    skipList_Lists *new_node = new skipList_Lists(virus);
    new_node->setNext(this);
    return new_node;
}

// GETTERS
linkedListStringNode *skipList_Lists::getVirus()
{
    return this->virus;
}

skipList *skipList_Lists::getVaccinated(linkedListStringNode *virus)
{
    skipList_Lists *temp = this;
    while (temp != NULL)
    {
        if (temp->getVirus()->getString().compare(virus->getString()) == 0)
        {
            return temp->getVaccinated();
        }
        temp = temp->getNext();
    }
    return NULL;
}

skipList *skipList_Lists::getVaccinated()
{
    return this->vaccinated;
}

skipList *skipList_Lists::getNotVaccinated(linkedListStringNode *virus)
{
    skipList_Lists *temp = this;
    while (temp != NULL)
    {
        if (temp->getVirus()->getString().compare(virus->getString()) == 0)
        {
            return temp->getNotVaccinated();
        }
        temp = temp->getNext();
    }
    return NULL;
}

skipList *skipList_Lists::getNotVaccinated()
{
    return this->notVaccinated;
}

skipList_Lists *skipList_Lists::getNext()
{
    return this->next;
}

// SETTERS
void skipList_Lists::setVirus(linkedListStringNode *v)
{
    this->virus = v;
}

void skipList_Lists::setVaccinated(skipList *l, linkedListStringNode *virus)
{
    skipList_Lists *temp = this;
    while (temp != NULL)
    {
        if (temp->getVirus()->getString().compare(virus->getString()) == 0)
        {
            temp->setVaccinated(l);
            return;
        }
        temp = temp->getNext();
    }
    return;
}

void skipList_Lists::setVaccinated(skipList *l)
{
    this->vaccinated = l;
}

void skipList_Lists::setNotVaccinated(skipList *l, linkedListStringNode *virus)
{
    skipList_Lists *temp = this;
    while (temp != NULL)
    {
        if (temp->getVirus()->getString().compare(virus->getString()) == 0)
        {
            temp->setNotVaccinated(l);
            return;
        }
        temp = temp->getNext();
    }
    return;
}

void skipList_Lists::setNotVaccinated(skipList *l)
{
    this->notVaccinated = l;
}

void skipList_Lists::setNext(skipList_Lists *n)
{
    this->next = n;
}
