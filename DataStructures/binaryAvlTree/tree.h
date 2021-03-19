#ifndef TREE_H
#define TREE_H

#include "../../citizenRecords/citizen.h"

using namespace std;

class treeNode
{
public:
    treeNode();
    ~treeNode();

    /*  
    insert the key to the correct position and balance the tree.
    If the key already exists then the statuses are merged. If the status of the old citizen is not in the status of the new citizen.
    So we return the old citizen in the merged pointer.
    But if the status of the old citizen is in the status of the new citizen then the duplicate is set to 1 to indicate that there was an error
    */
    treeNode *insert(treeNode *node, citizenRecord *citizen, citizenRecord **alreadyInTree, int *badDuplicate);
    treeNode *search(treeNode *root, int id);
    treeNode *newTreeNode(citizenRecord *citizen);
    treeNode *rightRotation(treeNode *y);
    treeNode *leftRotation(treeNode *x);
    int getBalance();

    // GETTERS
    citizenRecord *getCitizen();
    treeNode *getLeft();
    treeNode *getRight();
    int getKey();
    int getBalanceHeight();

    // SETTERS
    void setCitizen(citizenRecord *citizen);
    void setLeft(treeNode *l);
    void setRight(treeNode *r);
    void setKey(int id);
    void setBalanceHeight(int b);

    void print(treeNode *node);

private:
    treeNode *left;
    treeNode *right;
    int key;
    citizenRecord *citizen;
    int balanceHeight;
};

#endif