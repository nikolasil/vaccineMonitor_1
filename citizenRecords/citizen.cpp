#include <iostream>
#include <string>

#include "citizen.h"
#include "../util.h"
#include "../DataStructures/date/date.h"
#include "../DataStructures/linkedList/linkedListString.h"

listStatus::listStatus(linkedListStringNode *virus, linkedListStringNode *s, string d) : dateVaccinated(d)
{
    this->virusName = virus;
    this->status = s;
    this->next = NULL;
}

listStatus::listStatus(linkedListStringNode *virus, linkedListStringNode *s, date d) : dateVaccinated(d)
{
    this->virusName = virus;
    this->status = s;
    this->next = NULL;
}

listStatus::~listStatus()
{
    if (this->next != NULL)
    {
        delete this->next;
    }
}

void listStatus::addStatus(linkedListStringNode *virus, linkedListStringNode *s, string d)
{
    listStatus *temp = this;
    if (temp == NULL)
    {
        this->virusName = virus;
        this->status = s;
        this->dateVaccinated = d;
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    listStatus *new_node = new listStatus(virus, s, d);
    temp->next = new_node;
}

void listStatus::mergeStatus(listStatus *stat)
{
    listStatus *temp = this;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    listStatus *temp2 = stat;
    while (temp2 != NULL)
    {
        listStatus *new_node = new listStatus(temp2->getVirusName(), temp2->getVirusStatus(), temp2->getDateVaccinated());
        temp->next = new_node;
        temp = temp->next;
        temp2 = temp2->next;
    }
}

linkedListStringNode *listStatus::getVirusName()
{
    return this->virusName;
}

linkedListStringNode *listStatus::getVirusStatus()
{
    return this->status;
}

date listStatus::getDateVaccinated()
{
    return this->dateVaccinated;
}

linkedListStringNode *listStatus::getVirusStatus(linkedListStringNode *virus)
{
    listStatus *temp = this;
    do
    {
        if (temp->virusName->getString().compare(virus->getString()) == 0)
        {
            return temp->status;
        }
        temp = temp->next;
    } while (temp != NULL);
    return NULL;
}

date listStatus::getVirusDate(linkedListStringNode *virus)
{
    listStatus *temp = this;
    do
    {
        if (temp->virusName->getString().compare(virus->getString()) == 0)
        {
            return temp->dateVaccinated;
        }
        temp = temp->next;
    } while (temp != NULL);
    date nullDate("", "", "");
    return nullDate;
}

void listStatus::print()
{
    listStatus *temp = this;
    do
    {
        cout << "[virusName: ";
        temp->virusName->printData();
        cout << ", status: ";
        temp->status->printData();
        date nullDate("", "", "");
        if (temp->dateVaccinated.compare(nullDate) != 0)
        {
            cout << " , dateVaccinated: ";
            temp->dateVaccinated.print();
        }
        cout << "]";
        temp = temp->next;
    } while (temp != NULL);
}

citizenRecord::citizenRecord(int id, string name, string lastn, linkedListStringNode *count, int ag, listStatus *stat) : citizenID(id), firstName(name), lastName(lastn), country(count), age(ag), status(stat)
{
}

citizenRecord::citizenRecord(int id, string name, string lastn, linkedListStringNode *count, int ag, linkedListStringNode *virus, linkedListStringNode *stat, string d) : citizenID(id), firstName(name), lastName(lastn), country(count), age(ag)
{
    this->status = new listStatus(virus, stat, d);
}

citizenRecord::~citizenRecord()
{
    delete this->status;
}

void citizenRecord::print()
{
    cout << "citizenID: " << this->citizenID;
    cout << ", firstName: " << this->firstName;
    cout << ", lastName: " << this->lastName;
    cout << ", country: ";
    this->country->printData();
    cout << ", age: " << this->age << " ";
    this->status->print();
    cout << endl;
}

int citizenRecord::getID()
{
    return this->citizenID;
}

string citizenRecord::getFirstName()
{
    return this->firstName;
}

string citizenRecord::getLastName()
{
    return this->lastName;
}

linkedListStringNode *citizenRecord::getCountry()
{
    return this->country;
}

int citizenRecord::getAge()
{
    return this->age;
}

listStatus *citizenRecord::getStatus()
{
    return this->status;
}