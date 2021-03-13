#include <iostream>

#include "../DataStructures/skipList/skipList.h"

using namespace std;

int main(int argc, char *argv[])
{
    skipList *skiplist = new skipList();
    for (int i = 0; i < 5; i++)
    {
        skiplist->add(i);
    }

    // skiplist->print();
    // cout << endl;
    // skiplist->add(2);
    // skiplist->add(1);
    // skiplist->print();
    // cout << endl;
    // skiplist->remove(2);
    // cout << endl;

    cout << skiplist->search(2, 't') << endl;
    cout << skiplist->search(2, 'b') << endl;
    skiplist->print();
    cout << endl;
    delete skiplist;
    return 0;
}
