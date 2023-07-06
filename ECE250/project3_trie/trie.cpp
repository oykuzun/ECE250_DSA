#include "trie.h"
#include <iostream>
using namespace std;

trie::trie()
{
    trieNode *newNode = new trieNode(nullptr);
    setRoot(newNode);
    newNode->setTerminal(false); // created the new trie nothing is loaded yet
    this->numberOfWords = 0;
}

void trie::setRoot(trieNode *node)
{
    this->root = node;
}

trieNode *trie::getRoot()
{
    return this->root;
}

void trie::insert(string key, bool print)
{

    for (int c = 0; c < key.length(); c++)
    { // go through the string and check if any is out of bound
        if (key[c] < 'A' || key[c] > 'Z')
        {
            throw illegal_argument(); // in the main do the throw catch thing!!
        }
    }

    trieNode *temp = this->getRoot(); // start from the root set temp ptr to be the root ptr

    // key already exists in the trie
    if (search(key))
    {
        if (print)
        {
            cout << "failure" << endl;
        }
        return;
    }

    // if the key does not exist in the trie, insert
    else
    { //insert, not load
        for (int i = 0; i < key.length(); i++)
        {
            int indexArray = key[i] - 'A';
            if (!(temp->alphabetNode[indexArray]))
            {
                temp->alphabetNode[indexArray] = new trieNode(temp);
                temp->setNumberOfChildren((temp->getNumberOfChildren()) + 1);
            }
            temp = temp->alphabetNode[indexArray];
        }
        temp->setTerminal(true); // after the for loop the word is done - set the flag
        numberOfWords++;
        if (print)
        {
            cout << "success" << endl;
        }
    }
}

// return True if the word exists, else return False
bool trie::search(string key)
{
    trieNode *temp = this->getRoot();

    for (int i = 0; i < key.length(); i++)
    {
        int indexArray = key[i] - 'A';
        if (!(temp->alphabetNode[indexArray]))
        {
            return false; // the spot has not been filled meaning the key has not been inserted yet
        }
        temp = temp->alphabetNode[indexArray];
    }
    return temp->getTerminal();
}

bool trie::searchPrefix(string prefix)
{
    trieNode *temp = this->getRoot();

    for (int i = 0; i < prefix.length(); i++)
    {
        int indexArray = prefix[i] - 'A';
        if (!(temp->alphabetNode[indexArray]))
        {
            return false;
        }
        temp = temp->alphabetNode[indexArray];
    }
    return true;
}

void trie::countPrefix(string prefix)
{

    for (int c = 0; c < prefix.length(); c++)
    {
        if (prefix[c] < 'A' || prefix[c] > 'Z')
        {
            throw illegal_argument();
        }
    }

    // prefix doesnt exist - same search as searching for the word
    if (!searchPrefix(prefix))
    {
        cout << "not found" << endl;
        return;
    }

    // empty trie
    else if (this->numberOfWords == 0)
    {
        cout << "not found" << endl;
        return;
    }

    else
    {
        int countW = 0;
        trieNode *curr = searchNode(prefix);
        countHelper(curr, countW);
        cout << "count is " << countW << endl;
    }
}
// count the number of terminals after a node provided to the function
void trie::countHelper(trieNode *node, int &count)
{
    if (!(node))
    {
        return;
    }

    if (node->getTerminal())
    {
        count++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->alphabetNode[i] != nullptr)
        {
            countHelper(node->alphabetNode[i], count);
        }
    }
    return;
}

trieNode *trie ::searchNode(string key)
{
    trieNode *temp = this->root;

    for (int i = 0; i < key.length(); i++)
    {
        int indexArray = (key[i] - 'A');
        if (temp->alphabetNode[indexArray] == nullptr) //if the index is NULL return the node
        { 
            return temp;
        }

        temp = temp->alphabetNode[indexArray];
    }
    return temp;
}

void trie::display(trieNode *root)
{ // pass the root and call the helper function
    string s = "";

    if (getSize() == 0)
    { // nothing has been added
        return;
    }

    else
    {
        trieNode *root = this->root;
        printHelper(root, s); // pass the string by reference so that we get the edited string from the helper function
        cout << endl;
    }
}

void trie::printHelper(trieNode *node, string &s) {
    if (!(node))
    {
        return;
    }
    if (node->getTerminal())
    {
        cout << s << " ";
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->alphabetNode[i] != nullptr)
        {
            s.push_back(i + 'A'); //append to the string
            printHelper(node->alphabetNode[i], s);
            s.pop_back(); // delete the last element from the string as you are moving up
        }
    }
    return;
}

bool trie::isEmpty()
{
    if (this->numberOfWords == 0)
    {
        cout << "empty 1" << endl;
        return true;
    }
    else
    {
        cout << "empty 0" << endl;
        return false;
    }
}

int trie::getSize()
{
    return this->numberOfWords;
}

void trie::size()
{
    int count = this->numberOfWords;
    cout << "number of words is " << count << endl;
}

void trie::erase(string key)
{
    for (int c = 0; c < key.length(); c++)
    { // go through the string and check if any is out of bound
        if (key[c] < 'A' || key[c] > 'Z')
        {
            throw illegal_argument();
        }
    }

    trieNode *endOfWord = searchNode(key); // use this to check if this node has children or not

    // word is not in the trie
    if (!search(key))
    {
        cout << "failure" << endl;
        return;
    }

    // empty trie
    else if (this->numberOfWords == 0)
    {
        cout << "failure" << endl;
        return;
    }

    else if ((endOfWord->getNumberOfChildren()))
    { // has children so we only set the terminal flag
        endOfWord->setTerminal(false);
        numberOfWords--;
        cout << "success" << endl;
    }

    // a single branch, erase recursively using the parent
    else
    {
        int indexLetter = 0;

        for (int i = 0; i < key.length(); i++)
        {

            if (endOfWord->getNumberOfChildren() == 0)
            { //only recursively delete as long as it is not the end of the words
                indexLetter = key[key.length() - (i+1)] - 'A';
                trieNode *parent = endOfWord->getParent(endOfWord);
                delete (parent->alphabetNode[indexLetter]);
                parent->alphabetNode[indexLetter] = nullptr;
                endOfWord = parent;            
                endOfWord->setNumberOfChildren(endOfWord->getNumberOfChildren() - 1); // adjust the number of children

                if (endOfWord->getTerminal()){
                    cout << "success" << endl;
                    numberOfWords--;
                    return; // reached an end of word as traversing up - stop here
                }
            }
        }
        
        cout << "success" << endl;
        numberOfWords--;
    }
}

void trie::spellCheck(string word)
{

    trieNode *temp = this->getRoot();
    int count{0};

    if (search(word))
    {
        cout << "correct" << endl;
        return;
    }

    // checking the first letter if it exists or not
    int firstLetterIndex = word[0] - 'A';
    if (!(root->alphabetNode[firstLetterIndex]))
    {
        cout << endl;
        return;
    }

    else
    {
        string s = "";
        // scan the word and go to the node untiul you reach a null pointer for the character of the word and print everything after that node
        for (int i = 0; i < word.length(); i++)
        {
            int indexLetter = word[i] - 'A';

            if (!(temp->alphabetNode[indexLetter])) //if the node after is nullptr - doesn't exist in the trie, spellcheck
            {
                this->printHelper(temp, s); //print all the words with the prefix found
                cout << endl;
                return;
            }

            else
            {
                s.push_back(word[i]); // append to the string the character of the current node and move down the trie
                temp = temp->alphabetNode[indexLetter];
                count++;
            }
        }
        if(count == word.length()) { //in the right path but not the right word
            this->printHelper(temp, s); 
            cout << endl;
            return;
        }
    }
}

void trie::clear(trieNode *root)
{
    if (root != nullptr){
        for (int i = 0; i < 26; i++)
        {
            if (root->alphabetNode[i])
            {
                this->clear(root->alphabetNode[i]);
                delete root->alphabetNode[i];
            }
        }
        this->numberOfWords = 0;
    }

    else{ //empty trie
        this->numberOfWords = 0;
        return;
    }

}