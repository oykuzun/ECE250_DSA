#ifndef TRIENODE_H
#define TRIENODE_H
#include <iostream>
using namespace std;

class trieNode
{
private:
    bool terminal;
    trieNode *parent;
    int numberOfChildren; 

public:
    trieNode *alphabetNode[26]; //pointer from the array point to the next nodes
    trieNode(trieNode* parent);
    //~trieNode();

    // getters and setters for private variables
    void setTerminal(bool value);
    bool getTerminal();
    
    void setParent(trieNode*);
    trieNode* getParent(trieNode*);

    int getNumberOfChildren();
    void setNumberOfChildren(int n);
};

#endif 