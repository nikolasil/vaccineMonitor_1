#include <iostream>

#include "../DataStructures/skipList/skipList.h"

using namespace std;

int main(int argc, char *argv[])
{
    skipListLevel *a = new skipListLevel();
    a->add(7);
    a->add(5);
    a->add(6);
    a->add(8);
    a->add(9);
    skipListLevel *temp = a;
    while (temp != NULL)
    {
        temp->print();
        cout << endl;
        temp = temp->getUpLevel();
    }
    return 0;
}
