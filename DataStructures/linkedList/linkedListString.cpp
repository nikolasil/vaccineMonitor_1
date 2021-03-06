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
    if (this->next != NULL)
    {
        delete this->next;
    }
}

linkedListStringNode *linkedListStringNode::add(string d)
{
    if (this->data.compare("") == 0)
    {
        this->data = d;
        return this;
    }
    linkedListStringNode *new_node = new linkedListStringNode(d);
    new_node->next = this;
    return new_node;
}

linkedListStringNode *linkedListStringNode::remove(string d)
{
    linkedListStringNode *temp = this;
    linkedListStringNode *prev = NULL;

    if (temp != NULL && temp->data == d)
    {
        linkedListStringNode *temp2 = temp->next;
        delete temp;
        return temp2;
    }
    else
    {
        while (temp != NULL && temp->data != d)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
            return this;
        prev->next = temp->next;
        delete temp;
        return this;
    }
}

linkedListStringNode *linkedListStringNode::search(string d)
{
    linkedListStringNode *temp = this;
    while (temp != NULL)
    {
        if (temp->data.compare(d) == 0)
        {
            return temp;
        }

        temp = temp->next;
    }
    return temp;
}

string linkedListStringNode::getString()
{
    return this->data;
}

void linkedListStringNode::printData()
{
    cout << this->data;
}

void linkedListStringNode::print()
{
    linkedListStringNode *temp = this;
    while (temp != NULL)
    {
        temp->printData();
        cout << " ";
        temp = temp->next;
    }
    cout << endl;
}