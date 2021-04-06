/*
    This file contains the treeNode class.

    Is a self balanded tree that holds a pointer to a citizenRecord as data.


*/
#ifndef TREE_H
#define TREE_H

#include "../../citizenRecords/citizen.h"

using namespace std;

class treeNode
{
public:
    treeNode();
    ~treeNode();

    treeNode* insert(treeNode* node, citizenRecord* citizen, citizenRecord** alreadyInTree, string* result, bool checkNO);
    treeNode* search(treeNode* root, int id);
    treeNode* newTreeNode(citizenRecord* citizen);
    treeNode* rightRotation(treeNode* y);
    treeNode* leftRotation(treeNode* x);
    int getBalance();

    // GETTERS
    citizenRecord* getCitizen();
    treeNode* getLeft();
    treeNode* getRight();
    int getKey();
    int getBalanceHeight();

    // SETTERS
    void setCitizen(citizenRecord* citizen);
    void setLeft(treeNode* l);
    void setRight(treeNode* r);
    void setBalanceHeight(int b);

    void print(treeNode* node);

private:
    treeNode* left;
    treeNode* right;
    citizenRecord* citizen;
    int balanceHeight;
};

#endif