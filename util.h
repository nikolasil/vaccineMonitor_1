#ifndef UTIL_H
#define UTIL_H

#include <string>

using namespace std;

int checkArguments(int argc, char* argv[], string& filepath, int& bloomSize);
void checkNew(void* ptr);
string getInput(string prompt);
string* splitString(string input, int* length);

#endif