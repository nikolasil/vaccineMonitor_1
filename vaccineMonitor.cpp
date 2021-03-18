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
    if (length > 8)
    {
        cout << "ERROR IN RECORD";

        for (int i = 0; i < length; i++)
        {
            cout << " " << words[i];
        }
        cout << endl;
        return;
    }
    if (stoi(words[0]) > 9999 && stoi(words[0]) <= 0)
    {
        cout << input << endl;
        cout << "ID ERROR" << endl;
        delete[] words;
        return;
    }
    else if (stoi(words[4]) > 120 && stoi(words[4]) <= 0)
    {
        cout << input << endl;
        cout << "AGE ERROR" << endl;
        delete[] words;
        return;
    }
    if (words[6].compare("NO") != 0 && words[6].compare("YES") != 0)
    {
        cout << input << endl;
        cout << "YES/NO ERROR" << endl;
        delete[] words;
        return;
    }
    else if (length == 8 && (words[6].compare("NO") == 0))
    {
        cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << " " << words[7] << endl;
        cout << "NO WITH DATE ERROR" << endl;
        delete[] words;
        return;
    }
    else if (length == 7 && (words[6].compare("YES") == 0))
    {
        cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << endl;
        cout << "YES WITHOUT DATE ERROR" << endl;
        delete[] words;
        return;
    }

    if (countryList->search(words[3]) == NULL)
    {
        countryList = countryList->add(words[3]);
    }
    if (virusList->search(words[5]) == NULL)
    {
        virusList = virusList->add(words[5]);
        bloomList = bloomList->add(virusList);
        skiplist = skiplist->add(virusList);
    }
    char status = 'n';
    if (words[6].compare("YES") == 0)
    {
        status = 'y';
    }
    linkedListStringNode *country = countryList->search(words[3]);
    linkedListStringNode *virus = virusList->search(words[5]);
    if (length == 8) // YES
    {
        citizen = new citizenRecord(stoi(words[0]), words[1], words[2], country, stoi(words[4]), virus, status, words[7]);
        if (!citizen->getStatus()->getDateVaccinated().isValid())
        {
            cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << " " << words[7] << endl;
            cout << "DATE ERROR" << endl;
            delete[] words;
            return;
        }
    }
    else // NO
    {
        citizen = new citizenRecord(stoi(words[0]), words[1], words[2], country, stoi(words[4]), virus, status, "");
    }

    int duplicate = 0;
    citizenRecord *merged = NULL;
    // insert in tree
    tree = tree->insert(tree, citizen, &merged, &duplicate);

    if (!duplicate) // if not a bad duplicate
    {
        if (merged == NULL)
        {

            bloomList->getBloom(virus)->add(citizen->getID());
            if (status == 'y')
            {
                skiplist->getVaccinated(virus)->add(citizen->getID(), citizen);
            }
            else
            {
                skiplist->getNotVaccinated(virus)->add(citizen->getID(), citizen);
            }
        }
        else
        {

            bloomList->getBloom(virus)->add(merged->getID());
            if (status == 'y')
            {
                skiplist->getVaccinated(virus)->add(merged->getID(), merged);
            }
            else
            {
                skiplist->getNotVaccinated(virus)->add(merged->getID(), merged);
            }
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

void vaccineMonitor::populationStatus(string *arguments, int length)
{
    cout << "Selected: populationStatus" << endl;
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