#include "trieNode.h"
#include <iostream>
using namespace std;

//Constructor
trieNode::trieNode (trieNode* parent){
    this-> alphabetNode[26]; 
    for (int i = 0; i < 26; i++)
        this->alphabetNode[i] = nullptr;
    
    setTerminal(false);
    setNumberOfChildren(0);
    setParent(parent); //will pass a null pointer when creating the first node
 
}

void trieNode::setTerminal(bool value){
    this->terminal = value;
}

bool trieNode::getTerminal(){
    return this->terminal;
}

void trieNode::setParent(trieNode* parentPass){
    this->parent = parentPass;
}


trieNode* trieNode::getParent(trieNode* node){
    return node->parent; //return the parent of the node passed
}

void trieNode::setNumberOfChildren(int number){
    this->numberOfChildren = number;
}

int trieNode::getNumberOfChildren(){
    return this->numberOfChildren;
}
