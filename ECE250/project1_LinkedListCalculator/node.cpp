#include "node.h"
#include <iostream>
using namespace std;



// constructor
Node::Node(string name, double x) // overloading the constructor with parameters so when we are defininf a new var, we can call this constructor
{
    this->stringName = name;
    this->data = x;
    this->next = nullptr;
}

Node::Node() // default constructor
{
}

void Node::setStringName(string name)
{
    this->stringName = name;
}

string Node::getStringName()
{
    return this->stringName;
}

void Node::setData(double value)
{
    this->data = value; // set the node's data to the value specified to the setter
}

double Node::getData()
{
    return this->data;
}

void Node::setNextPointer(Node *nextNode)
{
    this->next = nextNode;
}

Node *Node::getNextPointer()
{
    return this->next;
}