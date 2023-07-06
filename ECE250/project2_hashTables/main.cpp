#include "hashTable.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    //input
    string cmd;
    bool command = false;

    //parameters
    hashTable *myHashTable;
    int N, P, PID, ADDR, x, m;

    while (cin>>cmd)
    {

        if (cmd == "OPEN"){
            command = true;
        }
    
        //for double hash
        if(command)
        {
            if(cmd == "M"){
                
                cin >> N >> P;
                myHashTable = new hashTable(N, P);

            }
            
            else if(cmd == "INSERT")
            {
                cin >> PID;
                myHashTable->insert_doubleHash(PID); 
            }

            else if(cmd == "SEARCH")
            {
                cin >> PID;
                myHashTable->search_double(PID);
            }
            
            else if(cmd == "WRITE")
            {
                cin >> PID >> ADDR >> x;
                myHashTable->writeDouble(PID, ADDR, x);
            }

            else if(cmd == "READ")
            {
                cin >> PID >> ADDR;
                myHashTable->readDouble(PID, ADDR);
            }

            else if(cmd == "DELETE")
            {
                cin >> PID;
                myHashTable->removeDouble(PID);
            }
            
            //no print since we use print only for chaining
            else if(cmd == "END")
            {
                delete myHashTable; // delete calls the destructor
            }
        }

        else{
            
            if(cmd == "M"){
                
                cin >> N >> P;
                myHashTable = new hashTable(N, P); 

            }
            
            else if(cmd == "INSERT")
            {
                cin >> PID;
                myHashTable->insert_chaining(PID); 
            }

            else if(cmd == "SEARCH")
            {
                cin >> PID;
                myHashTable->search_chaining(PID);
            }
            
            else if(cmd == "WRITE")
            {
                cin >> PID >> ADDR >> x;
                myHashTable->writeChaining(PID, ADDR, x);
            }

            else if(cmd == "READ")
            {
                cin >> PID >> ADDR;
                myHashTable->readChaining(PID, ADDR);
            }

            else if(cmd == "DELETE")
            {
                cin >> PID;
                myHashTable->removeChaining(PID);
            }
            
            else if (cmd == "PRINT")
            {
                cin >> m;
                myHashTable->print(m);
            }

            else if(cmd == "END")
            {
                delete myHashTable; // delete calls the destructor
            }
            
        }
    }
};