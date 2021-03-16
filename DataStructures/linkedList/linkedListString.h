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

    // GETTERS
    string getString();

    // SETTERS
    void setString(string s);

    void printData(); // print only this node
    void print();     // print this and all the next nodes

private:
    string data;
    linkedListStringNode *next;
};

#endif