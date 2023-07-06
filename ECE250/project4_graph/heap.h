#ifndef HEAP
#define HEAP

#include <iostream>
#include <vector>
#include <tuple>
#include "edge.h"
using namespace std;

class heap{
    private:
    vector<edge> heapVector;

    public:
    //heap();
    vector<edge> getHeapVector();
    int parent(int i);
    int left(int i);
    int right (int i);
    void insert(edge key);
    //void erase(edge);
    void heapify(int root);
    edge extractMin();
    bool checkHeapEmpty();

};

#endif
