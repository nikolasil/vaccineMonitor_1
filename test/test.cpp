#include <iostream>

#include "../DataStructures/skipList/skipList.h"

using namespace std;

int main(int argc, char *argv[])
{
    skipList *skiplist = new skipList();
    for (int i = 0; i < 50; i++)
    {
        skiplist->add(i);
    }

    skiplist->print();
    cout << skiplist->getCeiling()->getMyLevel() << endl;
    delete skiplist;
    return 0;
}
