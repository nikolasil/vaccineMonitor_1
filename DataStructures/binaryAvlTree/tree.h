#ifndef TREE_H
#define TREE_H

#include "../../citizenRecords/citizen.h"

using namespace std;

class treeNode
{
public:
    treeNode();
    ~treeNode();

    treeNode *insert(treeNode *node, citizenRecord *citizen, int *duplicate);
    // treeNode *remove(treeNode *node, citizenRecord *citizen);
    citizenRecord *getCitizen();
    void print(treeNode *node);
    treeNode *search(treeNode *root, int id);

    treeNode *left;
    treeNode *right;
    int key;

private:
    treeNode *newTreeNode(citizenRecord *citizen);
    treeNode *rightRotation(treeNode *y);
    treeNode *leftRotation(treeNode *x);

    int getBalance(treeNode *node);
    int getHeight(treeNode *node);

    citizenRecord *citizen;
    int balanceHeight;
};

#endif