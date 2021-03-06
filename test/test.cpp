#include <iostream>

// #include "../DataStructures/bloomFilter/bloomFilter.h"

using namespace std;

int coinFlip()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    return rand() % 2;
}

int coinFlip()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);

    return rand() % 2;
}

int main(int argc, char *argv[])
{
    // linkedListStringNode *statusList = new linkedListStringNode("YES");
    // linkedListStringNode *yes = statusList;
    // linkedListStringNode *no = statusList->add("NO");

    // bloomFilterList *bloomList = new bloomFilterList(100000);
    // bloomList = bloomList->add(no);
    // bloomList = bloomList->add(yes);
    // bloomFilter *bloomYES = bloomList->getBloom(yes);
    // bloomFilter *bloomNO = bloomList->getBloom(no);

    // bloomYES->add(4568);
    // bloomYES->add(4567);
    // bloomYES->add(4566);
    // cout << "check " << bloomYES->check(4568) << endl;
    // cout << "check " << bloomYES->check(4567) << endl;
    // cout << "check " << bloomYES->check(4566) << endl;
    // cout << "check " << bloomYES->check(4565) << endl;
    // cout << "check " << bloomYES->check(4566) << endl;
    // cout << "check " << bloomYES->check(4567) << endl;
    // cout << "check " << bloomYES->check(4568) << endl;
    // delete bloomList;
    // delete no;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* using nano-seconds instead of seconds */
    srand((time_t)ts.tv_nsec);

    printf("%d\n", coinFlip());

    return 0;
}
