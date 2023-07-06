#include "hashTable.h"
#include <iostream>
#include <vector>
using namespace std;

hashTable::hashTable(int memSize, int pageSize)
// this conctructor creates the four arrays needed for memory all arrays with 0s in all locations, set the member variables too
{
    this->count = 0;
    this->memorySize = memSize;
    this->pageSize = pageSize;
    this->numberOfPages = (memorySize / pageSize);
    int i,j;

    this->memoryAllocator = new int[numberOfPages]; // array of zeros in size m to be able to keep track of empty pages when we use chaining in hash table
    for (i = 0; i< this->numberOfPages; i++){
        memoryAllocator[i] = 0;
    }

    this->hash_double = new process[numberOfPages]; // created the hash table dynamically with size m=N/P
    
    this->hash_chain = new vector<process>[numberOfPages]; // array of vectors vector size

    this->memory = new int[memSize]; // created the memory array size N with all entries 0
    for (i = 0; i< this->numberOfPages; i++){
        memoryAllocator[i] = 0;
    }
    cout << "success" << endl;  
}

hashTable::~hashTable()
{
    delete[] memoryAllocator;
    delete[] memory;
    delete[] hash_double;
    delete[] hash_chain; 
}

void hashTable::search_chaining(int PID)
{

    int i;
    int check = 0;
    int probe = PID % (this->numberOfPages);

    for (i = 0; i < (this->hash_chain[probe].size()); i++)
    { // iterate throught he indices in the hash table that is linear for open addressing
        if (hash_chain[probe][i].getPID() == PID)
        {              
            check = PID; // set check to be the PID if found in the array, if not check will remain 0
        }
    }

    if (check == 0)
    {
        cout << "not found" << endl; // print not found since the PID is not existing in the hash funciton
        return;
    }

    else if (check == PID)
    {
        cout << "found " << check << " in " << probe << endl; // the position is the index of the hash table array not the vector
        return;
    }
}

bool hashTable::searchChainingBool(int PID)
{

    int i;
    int check = 0;
    int probe = PID % (this->numberOfPages);

    for (i = 0; i < (this->hash_chain[probe].size()); i++)
    {
        if (hash_chain[probe][i].getPID() == PID)
        {
            check = PID; // set check to be the PID if found in the array, if not check will remain 0
        }
    }

    if (check == 0)
    {
        return false; // the PID was not found since check was still 0
    }

    else
    {
        return true;
    }
}

void hashTable::search_double(int PID)
{
    bool check = false;
    int i;
    int probe = PID % this->numberOfPages;
    int offset = (PID/this->numberOfPages) % (this->numberOfPages);
    
    if(offset%2 == 0)
    {
        offset++;
    }

    for(i=0; i<numberOfPages; i++){
        int newProbe = (probe + (i * offset)) % this->numberOfPages;

        if (hash_double[newProbe].getPID() == PID){
            cout << "found " << (hash_double[newProbe].getPID()) << " in " << newProbe << endl;
            check = true;
            return;
        }

        else if (hash_double[newProbe].getFlag() == 0) {
            cout << "not found" << endl;
            return;
        }
    } 
    if (check == false) {
        cout << "not found" << endl;
        return;
    }
    
}

bool hashTable::searchDoubleBool(int PID)
{
    bool check = false;
    int i;
    int probe = PID % this->numberOfPages;
    int offset = int(PID / (this->numberOfPages)) % (this->numberOfPages);

    if(offset%2 == 0)
    {
        offset++;
    }

    for(i=0; i<numberOfPages; i++){
        int newProbe = (probe + (i * offset)) % this->numberOfPages;

        if (hash_double[newProbe].getPID() == PID){
            check = true;
            return check;
        }

        else if (hash_double[newProbe].getFlag() == 0) {
            return check;
        }
    } 
    return check;
}

void hashTable::insert_chaining(int PID)
{

    int probe = PID % this->numberOfPages;

    if (this->count >= this->numberOfPages)
    {
        cout << "failure" << endl;
        return;
    }

    if (searchChainingBool(PID))
    {
        cout << "failure" << endl;
        return;
    }

    int i;
    int pageAddressIndex = 0; // will be used to figure out what the page address is for the newly inserted process object

    // find the opening in the memory array
    for (i = 0; i < this->numberOfPages; i++)
    { // search through the memory allocator array which is size m to find the next empty spot in the array
        if (memoryAllocator[i] == 0)
        {
            pageAddressIndex = i;
        }
    }
    if (hash_chain[probe].empty())
    {
        hash_chain[probe].push_back(process(PID, (pageAddressIndex * pageSize), 0));
        memoryAllocator[pageAddressIndex] = PID; // set the memory allocator for chainig
        cout << "success" << endl;
        count++;
        return;
    }

    else{
        int i2; // to iterate through the vector
    // add sorted to the chain
        for (i2 = 0; i2 < this->hash_chain[probe].size(); i2++){ // linearly search through the vector in the probe's position in the main array
            if (hash_chain[probe][i2].getPID() < PID)
            {                                                                
                hash_chain[probe].insert(hash_chain[probe].begin() + i2, process(PID, (pageAddressIndex * this->getPageSize()), 0)); // insert the Process object with the constructor
                memoryAllocator[pageAddressIndex] = PID;  // set the int value to be the PID in the memory allocator array
                count++;
                cout << "success" << endl;
                return;
            }
        }
    }

}

void hashTable::insert_doubleHash(int PID)
{
    int probe = PID % this->numberOfPages;                                 // result from the primary hash function
    int offset = int(PID / (this->numberOfPages)) % (this->numberOfPages); // for the secondary hash function for double hashing

    if (offset % 2 == 0)
    {
        offset++;
    } // Since h2(𝑘) must be an odd number, you will add 1 to the resulting value if this value is even.

    // the hash table is full, there are m number of PIDs already
    if (this->count >= this->numberOfPages)
    {
        cout << "failure" << endl;
        return;
    }

    // check if the PID already exists in the hash table - LINEAR SEARCH NOW CREATE A BOOL FUNCTION FOR THIS THAT DOESNT DO THIS LINEARLY
    if (searchDoubleBool(PID))
    {
        cout << "failure" << endl;
        return;
    }
    
    int i = 0;
    int newProbe = (probe + (i * offset)) % this->numberOfPages;

    while (hash_double[newProbe].getFlag() == 1){
        i++;
        newProbe = (probe + (i * offset)) % this->numberOfPages;
    }

    hash_double[newProbe].setPID(PID); // set the PID for the process object to be the pid value, now we are in the process object - that's what is indexed here
    hash_double[newProbe].setPageAddress((this->pageSize) * newProbe);
    hash_double[newProbe].setFlag(1);
    cout << "success" << endl;
    count++;
    return;

}


void hashTable::writeChaining(int PID, int virtualAddress, int x)
{
    if (virtualAddress >= this->getPageSize())
    {
        cout << "failure" << endl; // the virtual address is larger than the page size, can not go that far
        return;
    }

    else if (!(searchChainingBool(PID)))
    { // if the PID is not present then we cant get to the page for that
        cout << "failure" << endl;
        return;
    }

    else
    { // ensured that there is a page for the pid
        memory[findPageNumberChaining(PID) + virtualAddress] = x; // will overwrite
        cout << "success" << endl;
    }
}

void hashTable::writeDouble(int PID, int virtualAddress, int x)
{
    if (virtualAddress >= this->getPageSize())
    {
        cout << "failure" << endl; // the virtual address is larger than the page size, can not go that far
        return;
    }

    else if (!(searchDoubleBool(PID)))
    { // if the PID is not present then we cant get to the page for that
        cout << "failure" << endl;
        return;
    }

    else
    {
        memory[findPageNumberDouble(PID) + virtualAddress] = x;
        cout << "success" << endl;
    }
}

void hashTable::readChaining(int PID, int virtualAddress)
{
    if (virtualAddress >= this->getPageSize())
    {
        cout << "failure" << endl;
        return;
    }

    else if (!(searchChainingBool(PID)))
    {
        cout << "failure" << endl;
        return;
    }

    else
    {
        int value = memory[findPageNumberChaining(PID) + virtualAddress];
        cout << virtualAddress << " " << value << endl;
    }
}

void hashTable::readDouble(int PID, int virtualAddress)
{
    if (virtualAddress >= this->getPageSize())
    {
        cout << "failure" << endl;
        return;
    }

    else if (!(searchDoubleBool(PID)))
    {
        cout << "failure" << endl;
        return;
    }

    else
    {
        int value = memory[findPageNumberDouble(PID) + virtualAddress];
        cout << virtualAddress << " " << value << endl;
    }
}

int hashTable::findPageNumberChaining(int PID)
{
    int i;
    int probe = PID % (this->numberOfPages);

    for (i = 0; i < (this->hash_chain[probe].size()); i++)
    { // iterate through the indices in the hash table that is linear for open addressing
        if (hash_chain[probe][i].getPID() == PID)
        {
            return (hash_chain[probe][i].getPageAddress()); // set check to be the PID if found in the array, if not check will remain 0
        }
    }
    return -1; // double check
}

int hashTable::findPageNumberDouble(int PID)
{
    int probe = PID % (this->numberOfPages);

    if (hash_double[probe].getPID() == PID)
    {
        return (hash_double[probe].getPageAddress());
    }

    else
    {
        int i;
        int offset = int(PID / (this->numberOfPages)) % (this->numberOfPages);
        
        if(offset%2 == 0)
        {
            offset++;
        }


        for (i = 1; i < (this->numberOfPages - 1); i++)
        {
            // update the probe with the offset:)
            int newProbe = ((probe + i * offset) % this -> numberOfPages);

            if (hash_double[newProbe].getPID() == PID)
            { // found the next empty spot
                return hash_double[newProbe].getPageAddress();
            }
        }
    }

    return -1;
}

void hashTable::removeChaining(int PID)
{
    if (!(searchChainingBool(PID)))
    {
        cout << "failure" << endl;
        return;
    }

    else
    {
        int i,j;
        int probe = PID % (this->numberOfPages);

        for (i = 0; i < (this->hash_chain[probe].size()); i++)
        {
            if (hash_chain[probe][i].getPID() == PID)
            { // found the process object
                hash_chain[probe][i].setPID(0);
                hash_chain[probe][i].setPageAddress(0);
                hash_chain[probe][i].setFlag(2);
                for (j = 0; i < this->numberOfPages; j++){ // search through the memory allocator array which is size m to find the next empty spot in the array,
                    if (memoryAllocator[j] == PID)
                        {
                            memoryAllocator[j] = 0;
                        }
                }   
                cout << "success" << endl;
                count--;
                return;
            }
        }
    }
}

void hashTable::removeDouble(int PID)
{
    if (!(searchDoubleBool(PID)))
    {
        cout << "failure" << endl;
        return;
    }

    else
    {
        int probe = PID % (this->numberOfPages);
        int i = 0;
        int offset = int(PID / (this->numberOfPages)) % (this->numberOfPages);
       
       if(offset%2 == 0)
        {
            offset++;
        }


        for (i = 0; i < (this->numberOfPages); i++)
        { // no need to limit how many times we can increement since we will find the pid for sure
            int newProbe = ((probe + i * offset) % this->numberOfPages);

            if (hash_double[newProbe].getPID() == PID)
            { // found the PID to be deleted
                hash_double[newProbe].setPID(0);
                hash_double[newProbe].setPageAddress(0);
                hash_double[newProbe].setFlag(2);
                cout << "success" << endl;
                count--;
                return;
            }
        }
    }
}

void hashTable::print(int m)
{
    if (hash_chain[m].empty())
    {
        cout << "chain is empty" << endl;
        return;
    }

    else
    {
        int i;

        for (i = 0; i < (this->hash_chain[m].size()); i++)
        {   // iterate throught the vector in index m
            cout << hash_chain[m][i].getPID() << " ";
        }
        cout<<endl;
    }
}

int hashTable::getMemorySize()
{
    return this->memorySize;
}

int hashTable::getPageSize()
{
    return this->pageSize;
}

int hashTable::getNumberOfPages()
{
    return this->numberOfPages;
}

int hashTable::getCount()
{
    return this->count;
}

void hashTable::setCount(int value)
{
    this->count = value;
}