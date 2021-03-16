#include <iostream>
#include <sstream>
#include <sys/stat.h>

#include "util.h"

int checkArguments(int argc, char *argv[], string &filepath, int &bloomSize)
{
    struct stat buffer;
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
    return 1;
}

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