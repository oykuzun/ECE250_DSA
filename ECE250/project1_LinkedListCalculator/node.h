#include <iostream>
using namespace std;

class Node
{
private:
    string stringName; // string name to set the name of the node
    double data;
    Node *next; // create a new object node

public:
    // constructor and destructor for the node class
    Node(string name, double x);
    Node();
    //~Node();
    // getters and setters for private variables
    void setStringName(string name);
    string getStringName(); // get the name of the node from the data stored in the node
    void setData(double value);
    double getData();
    void setNextPointer(Node *);
    Node *getNextPointer(); // return a pointer for the next node
};
