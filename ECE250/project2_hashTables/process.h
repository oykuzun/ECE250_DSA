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

public:
    process(int PID, int pageAddress, int flagPassed);
    process();                  // default constructor

    int getPID();
    int getFlag();
    void setFlag(int flag);
    void setPID(int value);
    int getPageAddress();
    void setPageAddress(int value);
};
#endif