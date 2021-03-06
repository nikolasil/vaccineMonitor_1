#include <iostream>
#include <string>
#include <sstream>

#include "util.h"
#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"

string getInput(string prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

string *splitString(string input, int *length)
{
    int i = 1;
    string arg;

    istringstream str(input);

    while (str >> arg)
    {
        i++;
    }
    *length = i - 1;
    istringstream str2(input);
    string *arguments = new string[i - 1];
    i = 0;
    while (str2 >> arg)
    {
        arguments[i++] = arg;
    }
    return arguments;
}

void vaccineStatusBloom(string *arguments, treeNode *tree, linkedListStringNode *virusList, bloomFilterList *bloomList)
{
    cout << "Selected: vaccineStatusBloom" << endl;
    int id = stoi(arguments[1]);
    string virus = arguments[2];
    treeNode *citizen = tree->search(tree, id);
    if (citizen != NULL)
    {
        // citizenID exists
        if (virusList->search(virus) != NULL)
        {
            int res = bloomList->getBloom(virusList->search(virus))->check(id);
            if (res)
            {
                cout << "MAYBE" << endl;
            }
            else
            {
                cout << "NOT VACCINATED" << endl;
            }
        }
        else
        {
            cout << "ERROR Virus name=" << virus << " dont exist in our database" << endl;
        }
    }
    else
    {
        cout << "ERROR Citizen with id=" << id << " dont exist in our database" << endl;
    }
}

void vaccineStatus(string *arguments)
{
    cout << "Selected: vaccineStatus" << endl;
}

void populationStatus(string *arguments)
{
    cout << "Selected: populationStatus" << endl;
}

void popStatusByAge(string *arguments)
{
    cout << "Selected: popStatusByAge" << endl;
}

void insertCitizenRecord(string *arguments)
{
    cout << "Selected: insertCitizenRecord" << endl;
}

void vaccinateNow(string *arguments)
{
    cout << "Selected: vaccinateNow" << endl;
}

void listNonVaccinatedPersons(string *arguments)
{
    cout << "Selected: list-nonVaccinated-Persons" << endl;
}

void teminate()
{
    cout << "Selected: exit" << endl;
}