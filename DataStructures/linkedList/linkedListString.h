#ifndef LINKEDLISTSTRING_H
#define LINKEDLISTSTRING_H

#include <string>

using namespace std;

class linkedListStringNode
{
public:
    linkedListStringNode();
    linkedListStringNode(string d);
    ~linkedListStringNode();

    linkedListStringNode *add(string d);
    linkedListStringNode *remove(string d);
    linkedListStringNode *search(string d);
    string getString();
    void printData();
    void print();

private:
    string data;
    linkedListStringNode *next;
};

#endif