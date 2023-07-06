#ifndef EDGE
#define EDGE

#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

class edge{
    private:
    tuple<int, int, int> edgeTuple;
    int weight;
    int vertex1;
    int vertex2;

    public:
    //constructor
    edge(int v1, int v2, int w);

    //tuples are immutable - only getters
    int getWeight();
    int getVertex1();
    int getVertex2();
    // void setWeight(int weight);
    // void setVertex1(int v1);
    // void setVertex2(int v2);
};

#endif