#ifndef TRIE
#define TRIE
#include "trieNode.h"
#include <iostream>
using namespace std;

class illegal_argument : public std::exception {
    
};

class trie{
    
    private:
    trieNode *root;
    int numberOfWords;

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
