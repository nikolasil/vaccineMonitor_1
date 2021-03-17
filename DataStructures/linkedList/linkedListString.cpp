#include <iostream>

#include "linkedListString.h"

linkedListStringNode::linkedListStringNode() : data("")
{
}

linkedListStringNode::linkedListStringNode(string d) : data(d)
{
}

linkedListStringNode::~linkedListStringNode()
{
    if (this->getNext() != NULL)
    {
        delete this->getNext();
    }
}

linkedListStringNode *linkedListStringNode::add(string d)
{
    if (this->getString().compare("") == 0)
    {
        this->setString(d);
        return this;
    }
    linkedListStringNode *new_node = new linkedListStringNode(d);
    new_node->setNext(this);
    return new_node;
}

linkedListStringNode *linkedListStringNode::remove(string d)
{
    linkedListStringNode *temp = this;
    linkedListStringNode *prev = NULL;

    if (temp != NULL && temp->getString() == d)
    {
        linkedListStringNode *temp2 = temp->getNext();
        delete temp;
        return temp2;
    }
    else
    {
        while (temp != NULL && temp->getString() != d)
        {
            prev = temp;
            temp = temp->getNext();
        }
        if (temp == NULL)
            return this;
        prev->setNext(temp->getNext());
        delete temp;
        return this;
    }
}

linkedListStringNode *linkedListStringNode::search(string d)
{
    linkedListStringNode *temp = this;
    while (temp != NULL)
    {
        if (temp->getString().compare(d) == 0)
        {
            return temp;
        }

        temp = temp->getNext();
    }
    return temp;
}

// GETTERS
string linkedListStringNode::getString()
{
    return this->data;
}

linkedListStringNode *linkedListStringNode::getNext()
{
    return this->next;
}

// SETTERS
void linkedListStringNode::setString(string s)
{
    this->data = s;
}

void linkedListStringNode::setNext(linkedListStringNode *n)
{
    this->next = n;
}

void linkedListStringNode::printData()
{
    cout << this->getString();
}

void linkedListStringNode::print()
{
    linkedListStringNode *temp = this;
    while (temp != NULL)
    {
        temp->printData();
        cout << " ";
        temp = temp->getNext();
    }
    cout << endl;
}