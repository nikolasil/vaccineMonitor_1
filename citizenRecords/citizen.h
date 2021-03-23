#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>

#include "../DataStructures/date/date.h"
#include "../DataStructures/linkedList/linkedListString.h"

using namespace std;

class listStatus
/* this class is a linked list that holds the
the viruses statuses that a citizen can have */
{
public:
    // 2 different constructors where the date is string or class date
    listStatus(linkedListStringNode *virus, char s, string d);
    listStatus(linkedListStringNode *virus, char s, date d);
    ~listStatus();

    void addStatus(linkedListStringNode *virus, char s, date d); /* add in the end of the list a new virus status */

    char getVirusStatus(linkedListStringNode *virus); //   given the virus name return the status of that virus.
    char getVirusStatus(string virus);                //   '\0' if that virus is not in that citizen list

    date getVirusDate(linkedListStringNode *virus); //   given the virus name return the date of that virus
    date getVirusDate(string virus);                //     EMPTY DATE if that virus is not in that citizen list

    // GETTERS
    linkedListStringNode *getVirusName();
    char getVirusStatus();
    date getDateVaccinated();

    void print();

private:
    linkedListStringNode *virusName;
    char status; // 'y' stands for "YES", 'n' for "NO"
    date dateVaccinated;
    listStatus *next;
};

class citizenRecord
{
public:
    citizenRecord(int id, string name, string lastn, linkedListStringNode *count, int ag, listStatus *stat);
    citizenRecord(int id, string name, string lastn, linkedListStringNode *count, int ag, linkedListStringNode *virus, char stat, string d);
    ~citizenRecord();

    int credentialsMatches(citizenRecord *citizen);

    // GETTERS
    int getID();
    string getFirstName();
    string getLastName();
    linkedListStringNode *getCountry();
    int getAge();
    listStatus *getStatus();

    void print();

private:
    int citizenID;
    string firstName;
    string lastName;
    linkedListStringNode *country;
    int age;
    listStatus *status;
};

#endif