#include "linkedList.h"
#include <iostream>
using namespace std;


void LinkedList::setHead(Node *head)
{
    this->headPointer = head;
}

Node *LinkedList::getHead()
{
    return this->headPointer;
}

void LinkedList::setTail(Node *tail)
{
    this->tailPointer = tail;
}

Node *LinkedList::getTail()
{
    return this->tailPointer;
}

void LinkedList::setSize(int size)
{
    this->sizeList = size;
}

int LinkedList::getSize()
{
    return this->sizeList;
void LinkedList::setCapacity(int capacity)
{
    this->capacityList = capacity;
}

int LinkedList::getCapacity()
{
    return this->capacityList;
}

LinkedList::LinkedList(int N)
{
    this->capacityList = N; 
    this->setSize(0);
    headPointer = nullptr; // node variables are null
    tailPointer = headPointer;
    link = nullptr;
}

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
    Node *p = this->headPointer;
    Node *t = this->headPointer;
    while (p != nullptr)
    {
        t = p;
        p = p->getNextPointer();
        delete t; // delete the contents that the head pointer was pointing to
        t = nullptr; // now update the head pointer to be p which was the temp
        // at the end our hea dpointer will be null
    }
    p = nullptr;
    headPointer = nullptr;
    link = nullptr;
}

void LinkedList::insert(string name, double x) //adding to the beginning and the end makes no difference
{
    if (this->sizeList < this->capacityList)
    {

        if (sizeList == 0) // inserting at the head when no nodes exist
        {
            Node *t = new Node(name, x); // create a pointer that points to a new node created with the values that the insert function takes
            headPointer = t;
            tailPointer = t;
            link = t;
            sizeList++;
            cout << "success" << endl;
            return;
        }

        else if (this->search(name))
        {
            cout << "failure" << endl ; //failure since the variable alr exists
            return;
        }

        else // inserting at the tail
        {
            Node *t = new Node(name, x); // create a pointer that points to a new node created with the values that the insert function takes
            this->tailPointer = t; // move the tail pointer to the new node added which is pointed to by t
            this->link->setNextPointer(tailPointer);
            this->tailPointer->setNextPointer(nullptr);
            link = link ->getNextPointer();
            sizeList++;                      
            cout << "success" << endl;
            return;
        }
    }

    cout << "failure" << endl; //failure since the list reached the limit and the function did not even enter the if statement    
}

bool LinkedList::search(string name)
{
    Node *p = headPointer; // start at the top of the list

    while (p != nullptr)
    {
        if (p->getStringName() == name)
        { // if key is in the list return the value
            return true;
        }
            p = p->getNextPointer();
    }
    return false;
}


Node* LinkedList::searchNode(string name) //return the pointer pointing tot he node
{
    Node *p = headPointer; // start at the top of the list

    while (p != nullptr)
    {
        if (p->getStringName() == name)
        {
            return p;
        }
            p = p->getNextPointer();
    }
    return nullptr;
}

Node* LinkedList::getPreviousNode(string name) //return the pointer for the previous node
{
    Node *p = headPointer;

    while (p != nullptr)
    {
        if (p->getNextPointer()->getStringName() == name)
        { // if key is in the list return the value
            return p;
        }
            p = p->getNextPointer();
    }
    return nullptr;
}

void LinkedList::print(string name)
{       
    if (search(name))
    {
        cout << searchNode(name)-> getData()<< endl;
    }

    else
    {
        cout<<"variable " << name << " not found" <<endl;
    }
}

void LinkedList::add(string x, string y, string z)
{
    if (!(this->search(x))) //check if the variables exist
        {
            cout<<"failure"<<endl;
            return;
        }
    else if (!(this->search(y)))
        {
            cout<<"failure"<<endl;
            return;
        }
    else if (!(this->search(z))) //z node has to be in the list
        {
            cout<<"failure"<<endl;
            return; // return so that we can exit the if statemetns if one of these conditions are satisfied
        }

    else //so all values exist in the list if we reached this point
    {
        this -> searchNode(z) -> setData(this->searchNode(x)->getData() + this -> searchNode(y)->getData());
        cout<<"success"<<endl;

    }
}

void LinkedList::subtract(string x, string y, string z)
{
    if (!(this->search(x)))
        {
            cout<<"failure"<<endl;
            return;
        }
    else if (!(this->search(y)))
        {
            cout<<"failure"<<endl;
            return;
        }
    else if (!(this->search(z)))
        {
            cout<<"failure"<<endl;
            return; // return so that we can exit the if statemetns if one of these conditions are satisfied
        }

    else
    {
        this -> searchNode(z) -> setData(this->searchNode(x)->getData() - this -> searchNode(y)->getData());
        cout<< "success" <<endl;
    }
}

void LinkedList::remove(string name)
{
    if (!(this->search(name)))
        {
            cout<<"failure"<<endl;
            return;
        }

    else if (this->searchNode(name) == this-> getHead()) // deleting if the value is in the head
    {
        Node *temp = this->searchNode(name);
        this->setHead(this->searchNode(name)->getNextPointer());//setting the head to be the next pointer fo the node with string name
        delete temp; // delete the value stored in the node with the string name
        sizeList--;
        cout<< "success" <<endl;
    }


    else if (this->searchNode(name) == this->getTail()) // deleting the value stored in the tail
    {
        Node *secondLast = this->headPointer;//start from the beginning of the list

        while (secondLast->getNextPointer()->getNextPointer() != nullptr) // next next is null since the next of the tail is null.
        {
            secondLast = secondLast->getNextPointer();
        }
        delete secondLast->getNextPointer();
        this->tailPointer = secondLast;
        this->link = secondLast;
        secondLast->setNextPointer(nullptr);
        sizeList--;
        cout<< "success" <<endl;
    }

    else // means that the value is somewhere in the middle/the element is the tail (2 element case)
    {
        Node *tempB = this->searchNode(name); // store the pointer pointer pointing to the node in the node in the middle and store it n tempB variable
        this->getPreviousNode(name)->setNextPointer(searchNode(name)->getNextPointer());
        delete tempB;
        sizeList--;
        cout<< "success" <<endl;
    }
}
