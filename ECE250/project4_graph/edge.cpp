#include "edge.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

edge::edge(int v1, int v2, int w){
    this->edgeTuple = make_tuple(v1, v2, w);
    this->vertex1 = get<0>(edgeTuple);
    this->vertex2 = get<1>(edgeTuple);
    this->weight = get<2>(edgeTuple);
}

int edge::getWeight(){
    return this->weight;
}

int edge::getVertex1(){
    return this->vertex1;
}

int edge::getVertex2(){
    return this->vertex2;
}