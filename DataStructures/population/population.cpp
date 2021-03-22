#include <iostream>
#include <iomanip>
#include "population.h"

yes::yes(unsigned int y) : y(y)
{
    this->next = NULL;
}

yes::~yes()
{
    if (next != NULL)
    {
        delete next;
    }
}

no::no(unsigned int n) : n(n)
{
    this->next = NULL;
}

no::~no()
{
    if (next != NULL)
    {
        delete next;
    }
}

noneInfo::noneInfo(unsigned int x) : noInfo(x)
{
    this->next = NULL;
}

noneInfo ::~noneInfo()
{
    if (next != NULL)
    {
        delete next;
    }
}

population::population(linkedListStringNode *c, bool byAge) : countryName(c)
{
    this->setNext(NULL);
    this->inRange = new yes(0);
    this->outRange = new yes(0);
    this->No = new no(0);
    this->noInformation = new noneInfo(0);
    if (byAge)
    {

        this->inRange->next = new yes(0);
        this->inRange->next->next = new yes(0);
        this->inRange->next->next->next = new yes(0);

        this->outRange->next = new yes(0);
        this->outRange->next->next = new yes(0);
        this->outRange->next->next->next = new yes(0);

        this->No->next = new no(0);
        this->No->next->next = new no(0);
        this->No->next->next->next = new no(0);

        this->noInformation->next = new noneInfo(0);
        this->noInformation->next->next = new noneInfo(0);
        this->noInformation->next->next->next = new noneInfo(0);
    }
}

population::~population()
{
    delete this->inRange;
    delete this->outRange;
    delete this->No;
    delete this->noInformation;
    if (this->next != NULL)
    {
        delete this->next;
    }
}

population *population::find(linkedListStringNode *country)
{
    population *temp = this;
    string countryName = country->getString();
    while (temp != NULL)
    {
        if (temp->getCountryName()->getString().compare(countryName) == 0)
        {
            return temp;
        }
        temp = temp->getNext();
    }
    return NULL;
}

void population::inYes(int pos)
{
    yes *temp = this->inRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->y++;
}

void population::outYes(int pos)
{
    yes *temp = this->outRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->y++;
}

void population::NO(int pos)
{
    no *temp = this->No;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->n++;
}

void population::noInfo(int pos)
{
    noneInfo *temp = this->noInformation;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    temp->noInfo++;
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
    yes *temp = this->inRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->y;
}

unsigned int population::getOutYes(int pos)
{
    yes *temp = this->outRange;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->y;
}

unsigned int population::getNO(int pos)
{
    no *temp = this->No;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->n;
}

unsigned int population::getNoInfo(int pos)
{
    noneInfo *temp = this->noInformation;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }
    return temp->noInfo;
}

void population::print()
{
    population *temp = this;
    while (temp != NULL)
    {
        if (temp->inRange->next == NULL)
        {
            double arithmitis = temp->inRange->y;
            double paranomastis = (temp->inRange->y + temp->outRange->y + temp->No->n + temp->noInformation->noInfo);
            double percentage;
            if (paranomastis == 0)
            {
                percentage = 0;
            }
            else
            {
                percentage = (arithmitis / paranomastis) * 100;
            }
            cout << fixed << setprecision(2) << temp->countryName->getString() << " " << temp->inRange->y << " " << percentage << "%" << endl;
        }
        else // byAge
        {
            cout << temp->countryName->getString() << endl;
            double arithmitis = temp->inRange->y;
            double paranomastis = (temp->inRange->y + temp->outRange->y + temp->No->n + temp->noInformation->noInfo);
            double percentage;
            if (paranomastis == 0)
            {
                percentage = 0;
            }
            else
            {
                percentage = (arithmitis / paranomastis) * 100;
            }
            cout << fixed << setprecision(2) << "0-20 " << temp->inRange->y << " " << percentage << "%" << endl;
            arithmitis = temp->inRange->next->y;
            paranomastis = (temp->inRange->next->y + temp->outRange->next->y + temp->No->next->n + temp->noInformation->next->noInfo);
            if (paranomastis == 0)
            {
                percentage = 0;
            }
            else
            {
                percentage = (arithmitis / paranomastis) * 100;
            }
            cout << fixed << setprecision(2) << "20-40 " << temp->inRange->next->y << " " << percentage << "%" << endl;
            arithmitis = temp->inRange->next->next->y;
            paranomastis = (temp->inRange->next->next->y + temp->outRange->next->next->y + temp->No->next->next->n + temp->noInformation->next->next->noInfo);
            if (paranomastis == 0)
            {
                percentage = 0;
            }
            else
            {
                percentage = (arithmitis / paranomastis) * 100;
            }
            cout << fixed << setprecision(2) << "40-60 " << temp->inRange->next->next->y << " " << percentage << "%" << endl;
            arithmitis = temp->inRange->next->next->next->y;
            paranomastis = (temp->inRange->next->next->next->y + temp->outRange->next->next->next->y + temp->No->next->next->next->n + temp->noInformation->next->next->next->noInfo);
            if (paranomastis == 0)
            {
                percentage = 0;
            }
            else
            {
                percentage = (arithmitis / paranomastis) * 100;
            }
            cout << fixed << setprecision(2) << "60+ " << temp->inRange->next->next->next->y << " " << percentage << "%" << endl;
            cout << endl;
        }
        temp = temp->getNext();
    }
}