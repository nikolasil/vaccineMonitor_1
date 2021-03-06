#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>

#include "../DataStructures/date/date.h"
#include "../DataStructures/linkedList/linkedListString.h"

using namespace std;

class listStatus
{
public:
    listStatus(linkedListStringNode *virus, linkedListStringNode *s, string d);
    listStatus(linkedListStringNode *virus, linkedListStringNode *s, date d);
    ~listStatus();

    void addStatus(linkedListStringNode *virus, linkedListStringNode *s, string d);
    void mergeStatus(listStatus *stat);
    linkedListStringNode *getVirusStatus(linkedListStringNode *virus);
    date getVirusDate(linkedListStringNode *virus);

    linkedListStringNode *getVirusName();
    linkedListStringNode *getVirusStatus();
    date getDateVaccinated();

    void print();

private:
    linkedListStringNode *virusName;
    linkedListStringNode *status;
    date dateVaccinated;
    listStatus *next;
};

class citizenRecord
{
public:
    citizenRecord(int id, string name, string lastn, linkedListStringNode *count, int ag, listStatus *stat);
    citizenRecord(int id, string name, string lastn, linkedListStringNode *count, int ag, linkedListStringNode *virus, linkedListStringNode *stat, string d);
    ~citizenRecord();

    void print();

    int getID();
    string getFirstName();
    string getLastName();
    linkedListStringNode *getCountry();
    int getAge();
    listStatus *getStatus();

private:
    int citizenID;
    string firstName;
    string lastName;
    linkedListStringNode *country;
    int age;
    listStatus *status;
};

#endif