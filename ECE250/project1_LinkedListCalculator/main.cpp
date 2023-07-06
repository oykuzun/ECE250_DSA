#include "linkedList.h"
#include <iostream>
using namespace std;

int main() {

    //input
    string cmd;

    //parameters
    LinkedList *linkedList1;
    int N;
    double val;
    string x, y, z;
    string name;

    while (cin>>cmd)
    {
        if(cmd == "CRT")
        {
            cin >> N;
            //call the linked list class
            linkedList1 = new LinkedList(N); //why asteriks
            cout<<"success"<<endl;
        }

        else if(cmd == "DEF")
        {
            cin >> name >> val;
            linkedList1->insert(name, val);
        }

        else if(cmd == "ADD")
        {
            cin >> x >> y >> z;
            linkedList1->add(x, y, z);
        }

        else if(cmd == "SUB")
        {
            cin >> x >> y >> z;
            linkedList1->subtract(x, y, z);
        }

        else if(cmd == "REM")
        {
            cin >> name;
            linkedList1->remove(name);
        }
     

        else if(cmd == "PRT")
        {
            cin >> name;
            linkedList1->print(name);
        }

        else if(cmd == "END")
        {
            delete linkedList1; //delete keyword calls the destructor
            linkedList1 = nullptr;
            return 0;
        }
    }

}