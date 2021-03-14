#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include "util.h"
#include "DataStructures/date/date.h"
#include "DataStructures/binaryAvlTree/tree.h"
#include "DataStructures/linkedList/linkedListString.h"
#include "DataStructures/bloomFilter/bloomFilter.h"
#include "DataStructures/skipList/skipList.h"
#include "citizenRecords/citizen.h"

using namespace std;

int main(int argc, char *argv[])
{
    struct stat buffer;
    string filepath;
    int bloomSize;
    if (argc != 5)
    {
        cout << "The number of arguments given must be 4" << endl;
        return 0;
    }
    else if (string(argv[1]).compare("-c") == 0 && string(argv[3]).compare("-b") == 0)
    {
        if (stat(argv[2], &buffer) != 0)
        {
            cout << "The file " << argv[1] << " don't exists" << endl;
            return 0;
        }
        if (atoi(argv[4]) <= 0)
        {
            cout << "The BloomSize must be positive" << endl;
            return 0;
        }
        filepath = string(argv[2]);
        bloomSize = atoi(argv[4]);
    }
    else if (string(argv[1]).compare("-b") == 0 && string(argv[3]).compare("-c") == 0)
    {
        if (stat(argv[4], &buffer) != 0)
        {
            cout << "The file " << argv[1] << " don't exists" << endl;
            return 0;
        }
        if (atoi(argv[2]) <= 0)
        {
            cout << "The BloomSize must be positive" << endl;
            return 0;
        }
        filepath = string(argv[4]);
        bloomSize = atoi(argv[2]);
    }
    else
    {
        cout << "-c filepath -b BloomSize || -b BloomSize -c filepath" << endl;
        return 0;
    }

    cout << "- - - vaccineMonitor started - - -" << endl;
    cout << "Loading file of records / Creating data structures" << endl;
    ifstream file(filepath);
    string line;
    treeNode *tree = NULL;
    linkedListStringNode *countryList = new linkedListStringNode();
    linkedListStringNode *virusList = new linkedListStringNode();
    linkedListStringNode *statusList = new linkedListStringNode("YES");
    statusList = statusList->add("NO");
    bloomFilterList *bloomList = new bloomFilterList(bloomSize);
    skipList_Lists *skiplist = new skipList_Lists();

    while (getline(file, line))
    {
        // cout << line << endl;
        int length;
        citizenRecord *citizen;
        string *words = splitString(line, &length);
        if (length == 8 && (words[6].compare("NO") == 0))
        {
            cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << " " << words[7] << endl;
            delete[] words;
            continue;
        }
        else if (length == 7 && (words[6].compare("YES") == 0))
        {
            cout << "ERROR IN RECORD " << words[0] << " " << words[1] << " " << words[2] << " " << words[3] << " " << words[4] << " " << words[5] << " " << words[6] << endl;
            delete[] words;
            continue;
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
        linkedListStringNode *status = statusList->search(words[6]);
        linkedListStringNode *country = countryList->search(words[3]);
        linkedListStringNode *virus = virusList->search(words[5]);
        if (length == 8) // YES
        {
            citizen = new citizenRecord(stoi(words[0]), words[1], words[2], country, stoi(words[4]), virus, status, words[7]);
        }
        else // NO
        {
            citizen = new citizenRecord(stoi(words[0]), words[1], words[2], country, stoi(words[4]), virus, status, "");
        }
        int duplicate = 0;
        citizenRecord *merged = NULL;
        // cout << "out id=" << stoi(words[0]) << " " << citizen->getID() << endl;
        tree = tree->insert(tree, citizen, &merged, &duplicate);
        // cout << "out id=" << stoi(words[0]) << " " << citizen->getID() << endl;
        if (!duplicate)
        {
            if (merged == NULL)
            {
                // cout << "citizen id=" << stoi(words[0]) << " " << citizen->getID() << endl;
                bloomList->getBloom(virus)->add(citizen->getID());
                if (status->getString().compare("YES") == 0)
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
                // cout << "merged id=" << stoi(words[0]) << " " << citizen->getID() << endl;
                bloomList->getBloom(virus)->add(merged->getID());
                if (status->getString().compare("YES") == 0)
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
        }
        delete[] words;
    }
    file.close();
    cout << "Done loading records and creating data structures" << endl;
    cout << endl;
    linkedListStringNode *a = virusList->search("Smallpox");
    cout << endl;
    skiplist->getVaccinated(a)->print();
    cout << endl;
    skiplist->getNotVaccinated(a)->print();
    cout << endl;
    do
    {
        cout << endl;
        string input = getInput("Enter command: ");
        int length;
        string *command = splitString(input, &length);
        if (length > 0)
        {
            if (command[0].compare("/vaccineStatusBloom") == 0)
            {
                vaccineStatusBloom(command, tree, virusList, bloomList);
            }
            else if (command[0].compare("/vaccineStatus") == 0)
            {
                vaccineStatus(command);
            }
            else if (command[0].compare("/populationStatus") == 0)
            {
                populationStatus(command);
            }
            else if (command[0].compare("/popStatusByAge") == 0)
            {
                popStatusByAge(command);
            }
            else if (command[0].compare("/insertCitizenRecord") == 0)
            {
                insertCitizenRecord(command);
            }
            else if (command[0].compare("/vaccinateNow") == 0)
            {
                vaccinateNow(command);
            }
            else if (command[0].compare("/list-nonVaccinated-Persons") == 0)
            {
                listNonVaccinatedPersons(command);
            }
            else if (command[0].compare("/exit") == 0)
            {
                cout << "exit" << endl;
                delete[] command;
                break;
            }
            else
            {
                cout << "Invalid command! Try Again!" << endl;
            }
        }
        else
        {
        }
        delete[] command;
    } while (1);
    delete tree;
    delete countryList;
    delete virusList;
    delete statusList;
    delete bloomList;
    delete skiplist;
}