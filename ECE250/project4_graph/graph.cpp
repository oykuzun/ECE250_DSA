#include "graph.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;


int graph::getNumberOfVertices(){
    return this->numberOfVertices;
}

void graph::setNumberOfVertices(int value){
    this->numberOfVertices = value;
}


void graph::insert(int vertex1, int vertex2, int weight, bool print){

    if (vertex1 <= 0 || vertex1 > 50001 || vertex2 <= 0 || vertex2 > 50001 || weight <= 0){
        throw illegal_argument();
    }

    if (vertex1 == 50001 || vertex2 == 50001){
        throw illegal_argument();
    }
    if (checkEdge(vertex1, vertex2, weight)){ //only need to check one edge
        //the edge already exists int he graph, return
        if(print){
            cout<< "failure" << endl;
        }

        return;
    }

    else{ //edge CAN NOT exist if reached here

        bool v1Empty = graphArray[vertex1].empty();
        bool v2Empty = graphArray[vertex2].empty();

        if (v1Empty && v2Empty){ //NEITHER vertices exist, increment the vertexNumber by 2 and add the edges to both
            graphArray[vertex1].push_back(edge(vertex1, vertex2, weight));
            graphArray[vertex2].push_back(edge(vertex2, vertex1, weight));
            numberOfVertices += 2;
            
            vertices.push_back(vertex1);
            vertices.push_back(vertex2);

            //aviod duplicating the edge in the edgeVector - check the 
            if (print){
            cout << "success" << endl;
            }
            return;
        }
        
        if(v1Empty || v2Empty){ //either one of the vertices do not exist
            if (v1Empty){ //v1 did not exist
                vertices.push_back(vertex1);
            }

            if (v2Empty){//v2 did not exist
                vertices.push_back(vertex2);
            }

            graphArray[vertex1].push_back(edge(vertex1, vertex2, weight));
            graphArray[vertex2].push_back(edge(vertex2, vertex1, weight));
            numberOfVertices++;
            if (print){
            cout << "success" << endl;
            }

            return;
        }

        //if this step is reached, both vertices existed, just add the edges to both adjacency lists (vectors)
        graphArray[vertex1].push_back(edge(vertex1, vertex2, weight));
        graphArray[vertex2].push_back(edge(vertex2, vertex1, weight));
        numberOfVertices++;
        if (print){
            cout << "success" << endl;
        }
        return;
    }
}


bool graph::checkEdge(int vertex1Index, int vertex2Index, int weight){ //check for the edge in both of the adjacency lists for v1 and v2

    if (graphArray[vertex1Index].empty() ){
        return false;
        //since bidrectional, and we insert in both places, only checking one is enough
    }
    
    else{
        for (int i = 0; i < graphArray[vertex1Index].size(); i++){
            if (graphArray[vertex1Index].at(i).getVertex2() == vertex2Index){ //the edge exists in the vector corresponding to the edges connected to vertex1
                return true;
            }
        }
    }
    return false;
}

bool graph::checkEmpty(){

    if (this->getNumberOfVertices() ==0){
        return true;
    }
    
    else{
        return false;
    }
}

void graph::print(int vertex){

    if (vertex <= 0 || vertex > 50001 || vertex == 50001){
        throw illegal_argument();
    }

    if (checkEmpty()){ //graph is empty, no vertex exist
        cout << "failure" << endl;
        return;
    }

    if (graphArray[vertex].empty()){ //if the index of the array at the vertex index is empty - vertex does not exist
        cout << "failure" <<endl;
        return;
    }
    
    else{
        for (int i=0; i< graphArray[vertex].size(); i++){
            cout << (graphArray[vertex][i].getVertex2()) << " ";
            //idea is to access the vector in that index and then print the second entry of all the tuples
        }
        cout << endl; //new line after printing all the vertices
    }
}

void graph::erase(int vertex){

    if (vertex <= 0 || vertex > 50001 || vertex == 50001){
        throw illegal_argument();
    }

    if (getNumberOfVertices() == 0){ //graph is empty, no vertex exist
        cout << "failure" << endl;
        return;
    }

    if (graphArray[vertex].empty()){ //if the index of the array at the vertex index is empty - vertex does not exist
        cout << "failure" <<endl;
        return;
    }

    else{
        graphArray[vertex].clear();
        for (int vertexIndex = 0; vertexIndex<50001; vertexIndex++){
            for (int j = 0; j < graphArray[vertexIndex].size(); j ++){ //iterate through the vectors in the array to detect if there are any edges with my vertex
                if (graphArray[vertexIndex][j].getVertex2() == vertex){
                    graphArray[vertexIndex].erase(graphArray[vertexIndex].begin() + j);
                }
            }
        }
        
        for (int i = 0; i < vertices.size(); i ++){ //iterate through the vectors in the array to detect if there are any edges with my vertex
            if (vertices[i] == vertex){
                vertices.erase(vertices.begin() + i); //erase the deleted vertex from the vector 
            }
        }
        numberOfVertices--;
        cout << "success" <<endl;
        return;
    }

}

void graph::MST(bool cost){
    if (checkEmpty()){ //graph is empty, no vertex exist
        
        if (cost){
            cout << "cost is 0" << endl;
            return;
        }
        if(!cost){
            cout << "failure" << endl;
            return;
        }
    }

    //vector former function to append all the vertices in an array
    heap priorityQueue; //initialize the PQ
    vector<edge> MSTVector; //initialize the MST
    int vertexVisited = 0; //keep track of how many vertices we have visited
    
    //pick the first node as the source node

    int start = vertices[0]; // to get the random vertex to start from so go the first vertex added to the graph
    for (int i = 0; i < graphArray[start].size(); i++){
        priorityQueue.insert(graphArray[start][i]);
    }

    visited[start] = true; //save that we have visited the first vertex
    vertexVisited++;
    
    int k = 0;
    while (!(priorityQueue.checkHeapEmpty())){ //since MST will only have V-1 edges and our heap is edge based? this might be wrong
        
        edge minimum = priorityQueue.extractMin();
        if (visited[minimum.getVertex2()]){
            continue;
        }

        for (int i = 0; i < graphArray[minimum.getVertex2()].size(); i++){//add the adjacent edges of the next vertex which is V2
            bool canInsertPQ = true;//check if an edge with the same weight exists in the PQ already by iterating through the PQ
            for (int i = 0; i<priorityQueue.getHeapVector().size(); i++){ //to avoid duplicates in the MST, only insert to MST if the edge has not been inserted (to avoind 2 1 3 and 1 2 3 showing up)
                if (priorityQueue.getHeapVector()[i].getWeight() == minimum.getWeight()){ //if the weights match, cant insert to PQ
                    canInsertPQ = false;
                }
            }
            if ((!visited[graphArray[minimum.getVertex2()][i].getVertex2()]) && canInsertPQ){//if destination vertex has not been visited insert to the PQ
                priorityQueue.insert(graphArray[minimum.getVertex2()][i]);
            }
        }        
        MSTVector.push_back(minimum); //just for the insertion of the first minimum edge so that the MST is not empty when checking for 
        visited[minimum.getVertex2()] = true; //added all the edges for that vertex, set the flag
        vertexVisited++;
        k++;
    }
    //at the end of this while loop, MSTVector should have all the edges to be printed

    if(cost){//compute the cost and output that
        int costCalculated = 0;

        for (int i = 0; i<MSTVector.size(); i++){
            costCalculated += MSTVector[i].getWeight(); //append all the weights of the MST
        }
        cout << "cost is " << costCalculated << endl;
    } 
    
    if (!cost){//print the MST
        for (int i = 0; i<MSTVector.size(); i++){
            cout << (MSTVector[i].getVertex1()) << " " << (MSTVector[i].getVertex2()) << " " << (MSTVector[i].getWeight()) << " ";
        }
        cout << endl;
    }

    //reset the visited vector
    for (int i = 0; i<50001; i++){
        visited[i] = false;
    }

}