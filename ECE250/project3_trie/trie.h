#ifndef TRIE
#define TRIE
#include "trieNode.h"
#include <iostream>
using namespace std;

class illegal_argument : public std::exception {
    //public:

    //string message(){return "illegal argument";} //overwrote the message function in exception class
};

class trie{
    
    private:
    trieNode *root; //ptr always point to the root - this is a trie variable right not the node????
    int numberOfWords;
    //should there be a counter for the number of words? that counts the terminal 


    public:
    
    trie();
    void setRoot(trieNode*);
    trieNode* getRoot();
    void insert(string key, bool print);
    bool isEmpty();
    void clear(trieNode* root);
    int getSize();
    void size();
    void countPrefix(string prefix);
    bool searchPrefix(string prefix);
    bool search(string key);
    trieNode* searchNode(string key);
    void countHelper(trieNode* node, int &count);
    void display (trieNode* root);
    void printHelper(trieNode* node, string & s);
    void erase(string key);
    void spellCheck(string word);
};

#endif
