#include <iostream>
#include <string>
#include <fstream>

#include "vaccineMonitor.h"
#include "util.h"
#include "DataStructures/date/date.h"
#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"
#include "DataStructures/skipList/skipList.h"
#include "citizenRecords/citizen.h"

using namespace std;

vaccineMonitor::vaccineMonitor(int bloomSize)
{
    this->tree = NULL;
    this->countryList = new linkedListStringNode();
    this->virusList = new linkedListStringNode();
    this->bloomList = new bloomFilterList(bloomSize);
    this->skiplist = new skipList_Lists();
}

vaccineMonitor::~vaccineMonitor()
{
    delete tree;
    delete countryList;
    delete virusList;
    delete bloomList;
    delete skiplist;
}

void vaccineMonitor::addFromFile(string filepath)
{
    ifstream file(filepath);
    string line;
    while (getline(file, line))
    {
        addRecord(line);
    }
    file.close();
}

void vaccineMonitor::addRecord(string input)
{
    int length;
    string *words = splitString(input, &length);
    citizenRecord *citizen;

    if (this->checkSyntaxRecord(length, words, input)) // the record had syntax errors
    {
        return;
    }

    addNewVirus(words[5]);
    linkedListStringNode *virus = virusList->search(words[5]);
    addNewCountry(words[3]);
    linkedListStringNode *country = countryList->search(words[3]);

    char status = 'n';
    string date = "";
    if (words[6].compare("YES") == 0)
    {
        status = 'y';
        date = words[7];
    }

    citizen = new citizenRecord(stoi(words[0]), words[1], words[2], country, stoi(words[4]), virus, status, date);

    int badDuplicate = 0;
    citizenRecord *alreadyInTree = NULL;

    tree = tree->insert(tree, citizen, &alreadyInTree, &badDuplicate); // insert in tree

    if (!badDuplicate) // if not a bad duplicate
    {
        if (alreadyInTree == NULL)
        {
            alreadyInTree = citizen;
        }
        bloomList->getBloom(virus)->add(alreadyInTree->getID());
        if (status == 'y')
        {
            skiplist->getVaccinated(virus)->add(alreadyInTree->getID(), alreadyInTree);
        }
        else
        {
            skiplist->getNotVaccinated(virus)->add(alreadyInTree->getID(), alreadyInTree);
        }
    }
    else
    {
        if (length == 8)
        {
            cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << " " << words[7] << endl;
        }
        else
        {
            cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << endl;
        }
        cout << "BAD DUPLICATE ERROR" << endl;
    }
    delete[] words;
}

void vaccineMonitor::startMenu()
{
    do
    {
        cout << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "Available commands" << endl;
        cout << "   /vaccineStatusBloom citizenID virusName" << endl;
        cout << "   /vaccineStatus citizenID [virusName]" << endl;
        cout << "   /populationStatus [country] virusName date1 date2" << endl;
        cout << "   /popStatusByAge [country] virusName date1 date2" << endl;
        cout << "   /insertCitizenRecord citizenID firstName lastName country age virusName YES/NO [date] " << endl;
        cout << "   /vaccinateNow citizenID firstName lastName country age virusName" << endl;
        cout << "   /list-nonVaccinated-Persons virusName " << endl;
        cout << "   /exit" << endl;
        cout << endl;
        string input = getInput("Enter command: ");
        int length;
        string *command = splitString(input, &length);
        if (length > 0)
        {
            if (command[0].compare("/vaccineStatusBloom") == 0)
            {
                vaccineStatusBloom(command, length);
            }
            else if (command[0].compare("/vaccineStatus") == 0)
            {
                vaccineStatus(command, length);
            }
            else if (command[0].compare("/populationStatus") == 0)
            {
                populationStatus(command, length);
            }
            else if (command[0].compare("/popStatusByAge") == 0)
            {
                popStatusByAge(command, length);
            }
            else if (command[0].compare("/insertCitizenRecord") == 0)
            {
                insertCitizenRecord(command, length);
            }
            else if (command[0].compare("/vaccinateNow") == 0)
            {
                vaccinateNow(command, length);
            }
            else if (command[0].compare("/list-nonVaccinated-Persons") == 0)
            {
                listNonVaccinatedPersons(command, length);
            }
            else if (command[0].compare("/exit") == 0)
            {
                cout << "exit" << endl;
                delete[] command;
                break;
            }
            else
            {
                cout << "Invalid command!" << endl;
            }
        }
        else
        {
        }
        delete[] command;
    } while (1);
}

int vaccineMonitor::checkSyntaxRecord(int length, string *words, string input)
{
    if (length < 7 || length > 8) // record must be only 7 or 8 words
    {
        cout << "ERROR IN RECORD";

        for (int i = 0; i < length; i++)
        {
            cout << " " << words[i];
        }
        cout << endl;
        cout << "ARGUMENT LENGTH ERROR" << endl;
        delete[] words;
        return 1;
    }
    if (stoi(words[0]) > 9999 && stoi(words[0]) <= 0) // id is 4 digits
    {
        cout << input << endl;
        cout << "ID ERROR" << endl;
        delete[] words;
        return 1;
    }
    if (stoi(words[4]) > 120 && stoi(words[4]) <= 0) // age is from 1 to 120
    {
        cout << input << endl;
        cout << "AGE ERROR" << endl;
        delete[] words;
        return 1;
    }
    if (words[6].compare("NO") != 0 && words[6].compare("YES") != 0) // the 6 word must only be NO or YES
    {
        cout << input << endl;
        cout << "YES/NO ERROR" << endl;
        delete[] words;
        return 1;
    }
    if (length == 8 && (words[6].compare("NO") == 0)) // when we have 8 words the word must be YES
    {
        cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << " " << words[7] << endl;
        cout << "NO WITH DATE ERROR" << endl;
        delete[] words;
        return 1;
    }
    if (length == 7 && (words[6].compare("YES") == 0)) // when we have 7 words the word must be NO
    {
        cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << endl;
        cout << "YES WITHOUT DATE ERROR" << endl;
        delete[] words;
        return 1;
    }
    if (length == 8)
    {
        date checker(words[7]);
        if (!checker.isValid())
        {
            cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << " " << words[7] << endl;
            cout << "DATE ERROR" << endl;
            delete[] words;
            return 1;
        }
    }
    return 0;
}

void vaccineMonitor::addNewVirus(string virusName)
{

    if (virusList->search(virusName) == NULL) // if we dont have that virus add it to the list of viruses
    {                                         // and make the bloom filter and the skiplist for that virus
        virusList = virusList->add(virusName);
        bloomList = bloomList->add(virusList);
        skiplist = skiplist->add(virusList);
    }
}

void vaccineMonitor::addNewCountry(string countryName)
{
    if (countryList->search(countryName) == NULL) // if we dont have that country add it to the list of Countries
    {
        countryList = countryList->add(countryName);
    }
}

// COMMANDS
void vaccineMonitor::vaccineStatusBloom(string *arguments, int length)
{
    cout << endl;
    cout << "- Selected: /vaccineStatusBloom" << endl;
    if (length == 3)
    {
        int id;
        string virus = "";
        try
        {
            id = stoi(arguments[1]);
            virus = arguments[2];
        }
        catch (std::exception &e)
        {
            cout << "ERROR citizenID must be given as first argument && it must be an integer" << endl;
            cout << "ERROR virusName must be given as second argument" << endl;
            return;
        }
        cout << "- citizenID: " << id << endl;
        cout << "- virusName: " << virus << endl;
        cout << endl;
        int res;
        linkedListStringNode *v = virusList->search(virus);
        if (v != NULL)
        {
            res = bloomList->getBloom(v)->check(id);
        }
        else
        {
            cout << "NOT VACCINATED" << endl;
            return;
        }

        if (res)
        {
            cout << "MAYBE" << endl;
            return;
        }
        else
        {
            cout << "NOT VACCINATED" << endl;
            return;
        }
    }
    else
    {
        cout << "ERROR 2 Arguments must be given" << endl;
        cout << "ERROR Total arguments given was: " << length - 1 << endl;
        return;
    }
}

void vaccineMonitor::vaccineStatus(string *arguments, int length)
{
    cout << endl;
    cout << "- Selected: /vaccineStatus" << endl;
    if (length == 2 || length == 3)
    {
        int id;
        string virus = "";
        try
        {
            id = stoi(arguments[1]);
            if (length == 3)
            {
                virus = arguments[2];
            }
        }
        catch (std::exception &e)
        {
            cout << "ERROR citizenID must be given as first argument && it must be an integer" << endl;
            if (length == 3)
            {
                cout << "ERROR virusName must be given as second argument" << endl;
            }
            return;
        }
        cout << "- citizenID: " << id << endl;
        if (length == 3)
        {
            cout << "- virusName: " << virus << endl;
        }
        cout << endl;

        linkedListStringNode *v = virusList;
        do
        {
            if (v == NULL)
            {
                break;
            }
            if (length == 3)
            {
                v = virusList->search(virus);
            }
            skipList *l;
            if (v != NULL)
            {
                l = skiplist->getVaccinated(v);
                skipListNode *n = l->search(id, 't');
                if (n == NULL)
                {
                    if (length == 2)
                    {
                        cout << v->getString() << " NO" << endl;
                    }
                    else
                    {
                        cout << "NOT VACCINATED" << endl;
                    }
                }
                else
                {
                    if (length == 2)
                    {
                        cout << v->getString() << " YES ";
                        n->getCitizen()->getStatus()->getVirusDate(v).print();
                        cout << endl;
                    }
                    else
                    {
                        cout << "VACCINATED ON ";
                        n->getCitizen()->getStatus()->getVirusDate(v).print();
                        cout << endl;
                    }
                }
            }
            else
            {
                cout << "NOT VACCINATED" << endl;
            }
            if (length == 3)
            {
                break;
            }
            v = v->getNext();
        } while (1);
    }
    else
    {
        cout << "ERROR 1 or 2 Arguments must be given" << endl;
        cout << "ERROR Total arguments given was: " << length - 1 << endl;
        return;
    }
}

void vaccineMonitor::treeInOrderPopulationCountry(treeNode *node, population **stat, string country, string virus, date date1, date date2);
{
    if (node == NULL)
        return;
    treeInOrderPopulationCountry(node->getLeft(), country, virus, date1, date2);

    citizenRecord *citizen = node->getCitizen();
    if (citizen->getCountry().compare(country) == 0)
    {
        char citizenStatus = citizen->getStatus()->getVirusStatus(virus);
        date citizenDate = citizen->getStatus()->getVirusDate(virus);
        if (citizenStatus == 'y')
        {
            if (citizenDate.compare(date1) == 1 && citizenDate.compare(date2) == -1)
            {
            }
            else
            {
            }
        }
        else if (citizenStatus == 'n')
        {
            if (citizenDate.compare(date1) == 1 && citizenDate.compare(date2) == -1)
            {
            }
            else
            {
            }
        }
    }

    treeInOrderPopulationCountry(node->getRight(), country, virus, date1, date2);
}

void vaccineMonitor::populationStatus(string *arguments, int length)
{
    cout << "Selected: populationStatus" << endl;
    if (length == 4 || length == 5)
    {
        date date1("");
        date date2("");
        if (length == 5)
        {
            date1.setAll(arguments[3]);
            date2.setAll(arguments[4]);
        }
        else
        {
            date1.setAll(arguments[2]);
            date2.setAll(arguments[3]);
        }
        if (!date1.isValid() || !date2.isValid())
        {
            cout << "ERROR Dates are not in valid format" << endl;
            return;
        }
        else if (date1.compare(date2) == 1)
        {
            cout << "ERROR date1 > date2" << endl;
            return;
        }
        linkedListStringNode *country;
        linkedListStringNode *virus;
        if (length == 5)
        {
            cout << "- country: " << arguments[1] << endl;
            cout << "- virusName: " << arguments[2] << endl;
            cout << "- date1: " << arguments[3] << endl;
            cout << "- date2: " << arguments[4] << endl;
            cout << endl;

            if (this->countryList->search(arguments[1]) == NULL)
            { // not in countyList
                cout << arguments[1] << " 0 0%" << endl;
                return;
            }
            else
            {
                country = countryList->search(arguments[1]);
                if (this->virusList->search(arguments[2]) == NULL)
                {
                    cout << arguments[1] << " 0 0%" << endl;
                    return;
                }
                else
                {
                    virus = virusList->search(arguments[2]);

                    population *stat = population(this->countryList->search(country), false);
                    this->treeInOrderPopulation(tree, &stat, country, virus, date1, date2);
                    stat->print();
                    return;
                }
            }
        }
        else
        {
            cout << "- virusName: " << arguments[1] << endl;
            cout << "- date1: " << arguments[2] << endl;
            cout << "- date2: " << arguments[3] << endl;
            cout << endl;

            if (this->virusList->search(arguments[1]) == NULL)
            { // not in virusList
                linkedListStringNode *temp = countryList;
                while (temp != NULL)
                {
                    cout << temp->getString() << " 0 0%" << endl;
                    temp = temp->getNext();
                }
                return;
            }
            else
            {
                virus = virusList->search(arguments[1]);
                // calculate
                return;
            }
        }
    }
    else
    {
        cout << "ERROR 3 or 4 Arguments must be given" << endl;
        cout << "ERROR Total arguments given was: " << length - 1 << endl;
        return;
    }
}

void vaccineMonitor::popStatusByAge(string *arguments, int length)
{
    cout << "Selected: popStatusByAge" << endl;
}

void vaccineMonitor::insertCitizenRecord(string *arguments, int length)
{
    cout << "Selected: insertCitizenRecord" << endl;
}

void vaccineMonitor::vaccinateNow(string *arguments, int length)
{
    cout << "Selected: vaccinateNow" << endl;
}

void vaccineMonitor::listNonVaccinatedPersons(string *arguments, int length)
{
    cout << "Selected: list-nonVaccinated-Persons" << endl;
}

void vaccineMonitor::teminate()
{
    cout << "Selected: exit" << endl;
}