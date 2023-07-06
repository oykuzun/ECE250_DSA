#include "heap.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

//credit to the pseudocode provided by Prof. Ladan in her lecture slides 

int heap::parent(int i){
    return ((i-1)/2);
}

int heap::left(int i){
    return (2*i + 1);
}

int heap::right(int i){
    return (2*i + 2);
}

vector<edge> heap::getHeapVector(){
    return heapVector;
}

bool heap::checkHeapEmpty(){
    return heapVector.empty();
}

void heap::heapify(int root){ 
    //heapVector stores all edges with the weight which will be passed to this function as a pointer
    
    int smallest = root;

    if ((heapVector.size() > left(root)) && (heapVector[left(root)].getWeight() < heapVector[smallest].getWeight())){ //nested ifs? keep in mind
        smallest = left(root);
    }

    if ((heapVector.size() > right(root)) && (heapVector[right(root)].getWeight() < heapVector[smallest].getWeight())){
        smallest = right(root);
    }
    
    if(smallest != root){ //if the smallest weight edge index does not match with the root we started with (which should have the min weight)
        edge temp = heapVector[root];
        heapVector[root] = heapVector[smallest];//adjust the root edge
        heapVector[smallest] = temp;//put the root edge in the place of the smallest edge that replaced the root
        heapify(smallest);
    }
    return;
}


edge heap::extractMin(){
    
    edge min = heapVector[0];
    
    int heapSize = heapVector.size();
    heapVector[0] = heapVector[heapSize-1]; // move the last element which is the next smallest after the root in the palce of root
    //will this affect the root I extracted which has the min now?
    heapVector.pop_back(); //do i need to pop back from the heap vector? adjust the size?

    heapify(0); //call heapify from top to bottom
    return min;
}


void heap::insert(edge key){
    heapVector.push_back(edge(0,0,0)); //insert the element at the end
    int endHeap = heapVector.size() - 1;//index for the end of the heap (where we added the new key)

    while ((endHeap > 0) && (heapVector[parent(endHeap)].getWeight() > key.getWeight())){
        edge temp = heapVector[endHeap];
        heapVector[endHeap] = heapVector[parent(endHeap)];
        endHeap = parent(endHeap);
    }
    heapVector[endHeap] = key;
}

// void heap::insert(edge edge){
//     this->heapVector->push_back(edge);
//     int endHeap = this->heapVector->size() - 1;
//     heapify(this->heapVector, endHeap);//heapify bottom up not going to work i think, see clrs book insert!!!!!
//     return;
// }