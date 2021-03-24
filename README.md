# Nikolas Iliopoulos 1115201800332
## 1 Exercise System Programming

---

### General Notes

#### Compile & Run

Makefile is included. Use the command **make** to compile the source code.

To run the application use: **./vaccineMonitor -c inputFile.txt -b BloomSize**

> *Note* that the order of the arguments doesn't matter.
> ./vaccineMonitor -b BloomSize -c inputFile.txt 

#### Structure & Classes

##### Citizen Record

The files **citizenRecords/citizen.cpp** and **citizenRecords/citizen.h** contains the *citizenRecord class* and the *listStatus class*.
Every citizen has its own list where the viruses information is beeing stored.

> *Note* that in citizenRecord the country is a node of type linkedListStringNode which is a list that stores strings. This class is used to prevent data duplications for countries and viruses as the same country or virus name has to be referenced many times.

```cpp
class citizenRecord
{
public:
    //Functions
private:
    int citizenID;
    string firstName;
    string lastName;
    linkedListStringNode *country;
    int age;
    listStatus *status;
};
```
```cpp
class listStatus
{
public:
    //Functions
private:
    linkedListStringNode *virusName;
    char status; // 'y' stands for "YES", 'n' for "NO"
    date dateVaccinated;
    listStatus *next;
};
```

##### Binary AVL Tree

The files **DataStructures\binaryAvlTree\tree.cpp** and **DataStructures\binaryAvlTree\tree.h** contains the *treeNode class*.

I store the citizens in a self balanced tree in order to have O(log(n)) time complexity for insetion, deletion and search. As for time complexity for InOrder , PreOrder and PostOrder traversal its O(n).

The key in the tree is the citizenID that is stored in the citizenRecord *citizen pointer. I access the id that way in order not to store an integer in the treeNode for less data duplication.


```cpp
class treeNode
{
public:
    //Functions
private:
    treeNode *left;
    treeNode *right;
    citizenRecord *citizen;
    int balanceHeight;
};
```

##### Bloom Filter

The files **DataStructures\bloomFilter\bloomFilter.cpp** and **DataStructures\bloomFilter\bloomFilter.h** contains the *bloomFilter class* and *bloomFilterList class*.

The bloom filter class is just a char type array that uses bitwise shifting to manipulate the bits.
I used char because sizeof(char) equals 1 Byte and it was helpful for calculations.
For hashing i used the **djb2**, **sdbm** and **hash_i** provided.

I created a list of type bloomFilterList where i store a bloom filter for every new virus that i come across.

```cpp
class bloomFilter
{
public:
    //Functions
private:
    int bloomSize;
    char *array;
};
```
```cpp
class bloomFilterList
{
public:
    //Functions
private:
    int bloomSize;
    linkedListStringNode *virus;
    bloomFilter *bloom;
    bloomFilterList *next;
};
```

##### Date

The files **DataStructures\date\date.cpp** and **DataStructures\date\date.h** contains the *date class*.

These class is just used to store the date but more importantly to check for its validity and compare it between other dates.

```cpp
class date
{
public:
    //Functions
private:
    string day;
    string month;
    string year;
};
```

##### LinkedListStringNode

The files **DataStructures\linkedList\linkedListString.cpp** and **DataStructures\linkedList\linkedListString.h** contains the *LinkedListStringNode class*.



```cpp
class LinkedListStringNode
{
public:
    //Functions
private:
    string data;
    linkedListStringNode *next;
};
```

---

#### CitizenRecords Checking

### DataStructures

### Commands

### Script

The script is inside the directory **/script** with the name **script.sh**.