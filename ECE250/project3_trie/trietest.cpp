#include "trie.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){

    trie myTrie;
    string cmd;
    string addWord;
    trieNode *root = myTrie.getRoot();

    while(cin >> cmd)
    {
        if  (cmd == "load")
        {
            ifstream fin("corpus.txt");
            while (fin >> addWord)
            {
                myTrie.insert(addWord, false);

            }
                fin.close();
            cout << "success" << endl;
        }
        
        else if(cmd == "i") //INSERT
        {
            try{
                cin >> addWord;
                myTrie.insert(addWord, true);
            }

            catch(illegal_argument e){
            cout << "illegal argument" << endl;
            }
            
        }

        else if(cmd == "c") //COUNT PREFIX
        {
            try{
                cin >> addWord;
                myTrie.countPrefix(addWord);
            }

            catch(illegal_argument e){
            cout << "illegal argument" << endl;
            }
            
        }

        else if(cmd == "e") //ERASE
        {
            try{
                cin >> addWord;
                myTrie.erase(addWord);
            }

            catch(illegal_argument e){
            cout << "illegal argument" << endl;
            }
            
        }

        else if(cmd == "p") //PRINT ALL WORDS
        {   
            myTrie.display(root);
        }

        else if (cmd == "spellcheck")
        {
            cin >> addWord;
            myTrie.spellCheck(addWord);

        }

        else if (cmd == "empty") //check if the trie is empty
        {
            myTrie.isEmpty();
        }

        else if (cmd == "clear")
        {
            myTrie.clear(root);
            delete root;
            root = new trieNode(nullptr);
            myTrie.setRoot(root);
            cout << "success" << endl;

        }

        else if (cmd == "size")
        {
            myTrie.size();
        }

        else if (cmd == "exit")
        {
            myTrie.clear(root);
            delete root;
        }
    }

}

