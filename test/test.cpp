#include <iostream>

#include "../DataStructures/skipList/skipList.h"

using namespace std;

int main(int argc, char *argv[])
{
    skipList *skiplist = new skipList();

    skiplist->add(5);
    skiplist->add(6);
    skiplist->add(7);
    skiplist->add(9);
    skiplist->add(8);
    skiplist->print();
    return 0;
}
