#include "population.h"

yes_no::yes_no(unsigned int y, unsigned int n, yes_no *next) : yes(y), no(n)
{
    this->next = NULL;
}

yes_no::~yes_no()
{
    if (next != NULL)
    {
        delete next;
    }
}

population::population(linkedListStringNode *c, bool byAge) : countryName(c)
{
    this->setNext(NULL);
    this->inRange = new yes_no(0, 0);
    this->outRange = new yes_no(0, 0);
    if (byAge)
    {
        this->inRange->next = new yes_no(0, 0);
        this->inRange->next->next = new yes_no(0, 0);
        this->inRange->next->next->next = new yes_no(0, 0);

        this->outRange->next = new yes_no(0, 0);
        this->outRange->next->next = new yes_no(0, 0);
        this->outRange->next->next->next = new yes_no(0, 0);
    }
}

population::~population()
{
    delete this->inRange;
    delete this->outRange;
}

void population::add(population **start, population *n)
{
    n->setNext(*start);
    n = (*start);
}

void population::inYes(int pos)
{
    yes_no *temp = this->inRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->yes++;
}

void population::inNo(int pos)
{
    yes_no *temp = this->inRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->no++;
}

void population::outYes(int pos)
{
    yes_no *temp = this->outRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->yes++;
}

void population::outNo(int pos)
{
    yes_no *temp = this->outRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->no++;
}

// SETTERS
void population::setNext(population *n)
{
    this->next = n;
}

// GETTERS
population *population::getNext()
{
    return this->next;
}

linkedListStringNode *population::getCountryName()
{
    return this->countryName;
}

unsigned int population::getInYes(int pos)
{
    yes_no *temp = this->inRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->yes;
}

unsigned int population::getInNo(int pos)
{
    yes_no *temp = this->inRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->no;
}

unsigned int population::getOutYes(int pos)
{
    yes_no *temp = this->outRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->yes;
}

unsigned int population::getOutNo(int pos)
{
    yes_no *temp = this->outRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->no;
}

void population::print()
{
    population *temp = this;
    while (temp != NULL)
    {
        if (temp->inRange->next == NULL)
        {
            // YES_in_range / (YES_overall + NO_overall)
            cout << temp->countryName->getString() << " " << temp->inRange->yes << " " << temp->inRange->yes / (temp->inRange->yes + temp->inRange->no + temp->outRange->yes + temp->outRange->no) << "%";
        }
        else // byAge
        {
            cout << temp->countryName->getString() << endl;
            cout << "0-20 " << temp->inRange->yes << " " << temp->inRange->yes / (temp->inRange->yes + temp->inRange->no + temp->outRange->yes + temp->outRange->no) << "%" << endl;
            cout << "20-40 " << temp->inRange->next->yes << " " << temp->inRange->next->yes / (temp->inRange->next->yes + temp->inRange->next->no + temp->outRange->next->yes + temp->outRange->next->no) << "%" << endl;
            cout << "40-60 " << temp->inRange->next->next->yes << " " << temp->inRange->next->next->yes / (temp->inRange->next->next->yes + temp->inRange->next->next->no + temp->outRange->next->next->yes + temp->outRange->next->next->no) << "%" << endl;
            cout << "60+ " << temp->inRange->next->next->next->yes << " " << temp->inRange->next->next->next->yes / (temp->inRange->next->next->next->yes + temp->inRange->next->next->next->no + temp->outRange->next->next->next->yes + temp->outRange->next->next->next->no) << "%" << endl;
        }
        temp = temp->getNext();
    }
}