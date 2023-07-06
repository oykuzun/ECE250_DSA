#ifndef HASHTABLE
#define HASHTABLE
#include "process.h"
#include <iostream>
#include <vector>
using namespace std;

class hashTable
{
private:
    int memorySize;
    int pageSize;
    int numberOfPages;
    int count; // count how many PIDs are stored currently
    int *memoryAllocator;
    process *hash_double;        // creating an array for the hash table with process type variables
    vector<process> *hash_chain; // vector of vectors that have processes in them for chaining
    int *memory;                 // pointer for the array of ints for the physical memory

public:
    hashTable(int pageSize, int memSize);
    ~hashTable();

    // getters and setters
    int getMemorySize();
    int getPageSize();
    int getNumberOfPages();
    int getCount();
    void setCount(int value);

    // P2 functions
    void insert_chaining(int PID);
    void insert_doubleHash(int PID);
    void search_double(int PID);
    void search_chaining(int PID);

    bool searchChainingBool(int PID);
    bool searchDoubleBool(int PID);

    int findPageNumberChaining(int PID);
    int findPageNumberDouble(int PID);
    void removeChaining(int PID);
    void removeDouble(int PID);
    void writeChaining(int PID, int virtualAddress, int x);
    void readChaining(int PID, int virtualAddress);
    void writeDouble(int PID, int virtualAddress, int x);
    void readDouble(int PID, int virtualAddress);
    void print(int m);
};

#endif