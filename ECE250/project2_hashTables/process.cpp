#include "process.h"
#include <iostream>
#include <vector>
using namespace std;

process::process(int valuePID, int pageAddress, int flagPassed)
{
    this->PID = valuePID;
    this->pageAddress = pageAddress;
    this-> flag = flagPassed;
}

process::process()
{
    this->PID = 0;
    this->pageAddress = 0;
    this-> flag = 0;
}

int process::getPID()
{
    return this->PID;
}

void process::setFlag(int passedFlag)
{
    this->flag = passedFlag;
}

int process::getFlag()
{
    return this->flag;
}

void process::setPID(int value)
{
    this->PID = value;
}

int process::getPageAddress()
{
    return this->pageAddress;
}

void process::setPageAddress(int value)
{
    this->pageAddress = value;
}