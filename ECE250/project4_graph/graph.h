#ifndef GRAPH
#define GRAPH

#include "edge.h"
#include "heap.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

const int infinty = __INT_MAX__;

class illegal_argument : public std::exception {
};

//array of vectors of tuples (tuple of threes) vertice, vertice, weight
//tuple representing an edge connecting two vertices with a weight

class graph{
    private:
    int numberOfVertices = 0;
    vector<edge> graphArray[50001]; //array of vectors of tuples (edges) to represent the graph
    vector<int> vertices{};

    bool visited[50001]{};//set to false
    vector<edge> MSTVector; //vector to append the edges to

    public:
    //graph();
    int getNumberOfVertices();
    void setNumberOfVertices (int value);
    bool checkEmpty();
    bool checkEdge(int vertex1Index, int vertex2Index, int weight);
    void print(int vertex);
    void erase(int vertex);
    void insert(int vertex1, int vertex2, int weight, bool print);
    void MST(bool cost);
};

#endif

