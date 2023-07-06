#include "graph.h"
#include <iostream>
#include <fstream>
using namespace std;

// need to remove before testing on linux!!!!!!
//#include "graph.cpp"

int main(){

    graph *myGraph = new graph;
    string cmd;
    string fileName;
    int vertex1;
    int vertex2;
    int weight;
    
    while(cin >> cmd)
    {
        if(cmd == "LOAD"){
            cin >> fileName;
            ifstream fin(fileName.c_str()); //Note that we are using the variable as the filename
            
            int num;
            fin >> num; //first line is the number of vertices

            while (fin >> vertex1 >> vertex2 >> weight)
            {
                myGraph->insert(vertex1, vertex2, weight, false);

            }
            fin.close();
            cout << "success" << endl;
        }

        if (cmd == "INSERT"){

            try{
                cin >> vertex1 >> vertex2 >> weight;
                myGraph->insert(vertex1, vertex2, weight, true);
            }

            catch(illegal_argument e){
            cout << "illegal argument" << endl;
            }

        }
        if (cmd == "PRINT"){

            try{
                cin >> vertex1;
                myGraph->print(vertex1);
            }

            catch(illegal_argument e){
            cout << "illegal argument" << endl;
            }
        }

        if  (cmd == "DELETE"){
            try{
                cin >> vertex1;
                myGraph->erase(vertex1);
            }

            catch(illegal_argument e){
            cout << "illegal argument" << endl;
            }
        }
        
        if  (cmd == "MST"){
            myGraph->MST(false);//false bc we do not want to compute the cost
        }
        if  (cmd == "COST"){
            myGraph->MST(true);
        }
        if (cmd == "END"){
            delete myGraph; //call the destructor of the graph
            break;
        }

    }
}