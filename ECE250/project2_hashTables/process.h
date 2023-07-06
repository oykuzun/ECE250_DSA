#ifndef PROCESS
#define PROCESS
#include <iostream>
#include <vector>
using namespace std;

class process
{
private:
    int PID;
    int pageAddress;
    int flag;
    // set the flag values so that when we pass unallocated, it is 0.
    //  const int UNALLOCATED = 0;
    //  const int ALLOCATED = 1;
    //  const int DELETED = 2;

public:
    process(int PID, int pageAddress, int flagPassed); // constructor ?? do i need a page adress here too? do we assign the page address after?
    process();                         // default constructor

    int getPID();
    int getFlag();
    void setFlag(int flag);
    void setPID(int value);
    int getPageAddress();
    void setPageAddress(int value);
};
#endif