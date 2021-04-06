/*
- - - citizenRecord Methods Iimplemantation - - -
*/

#ifndef STRINGLIST_H
#define STRINGLIST_H

#include <string>

using namespace std;

class stringList
{
public:
    stringList();
    stringList(string d);
    ~stringList();

    stringList* add(string d);
    stringList* remove(string d);
    stringList* search(string d);

    // GETTERS
    string getString();
    stringList* getNext();
    // SETTERS
    void setString(string s);
    void setNext(stringList* n);

    void printData(); // print only this node
    void print();     // print this and all the next nodes

private:
    string data;
    stringList* next;
};

#endif