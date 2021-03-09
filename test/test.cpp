#include <iostream>

#include "../DataStructures/skipList/skipList.h"

using namespace std;

int main(int argc, char *argv[])
{
    skipListNode *a = new skipListNode(5);

    a->print();
    a->remove(&a, 5);
    a->print();
    a->destroy();
    return 0;
}
