#include <iostream>

#include "../DataStructures/skipList/skipList.h"

using namespace std;

int main(int argc, char *argv[])
{
    linkedListStringNode *virus = new linkedListStringNode("nikolas");
    linkedListStringNode *virus2 = new linkedListStringNode("nikolas2");
    skipList_Lists *skiplist = new skipList_Lists(virus);
    skiplist = skiplist->add(virus2);
    skipList *vac = skiplist->getVaccinated(virus);
    skipList *nvac = skiplist->getNotVaccinated(virus);
    skipList *vac2 = skiplist->getVaccinated(virus2);
    skipList *nvac2 = skiplist->getNotVaccinated(virus2);

    vac->add(0);
    nvac->add(1);
    vac2->add(3);
    nvac2->add(4);
    vac->print();
    nvac->print();
    vac2->print();
    nvac2->print();
    cout << endl;
    delete skiplist;
    delete virus;
    delete virus2;
    return 0;
}
