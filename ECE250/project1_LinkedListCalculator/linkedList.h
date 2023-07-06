#include "node.h"
#include <iostream>
using namespace std;

class LinkedList
{
private:
    Node *headPointer; // create the head and tail pointer for the linked list- there is a var called head, it is apointer and it is pointing to a node
    Node *tailPointer;
    int sizeList; // in order to keep track of the size of the list
    int capacityList; // assign the input to the crt we pass the input to the crt function to capacity

public:
    Node *link;
    // constructor and destructor
    LinkedList(int N);
    LinkedList();  // default constructor
    ~LinkedList(); // destructor - clear function in the project def

    // setters and getters for the private variables
    void setHead(Node *head);
    Node *getHead(); // get the name of the node from the data stored in the node
    void setTail(Node *Tail);
    Node *getTail();
    void setSize(int size);
    int getSize();
    void setCapacity(int capacity);
    int getCapacity();
    Node *getPreviousNode(string name);

    // P1 functions
    void insert(string name, double x); // def command
    bool search(string name);
    Node *searchNode(string name);
    void remove(string name); //for remove three conditions within the function to check where we are removing if the
    //elenent is the first element so the str of the head is the same as the str of what's being removed, 
    //(same for tail) move head/tail accordingly and remove the element.
    void print(string name);
    void add(string x, string y, string z);
    void subtract(string x, string y, string z);
};