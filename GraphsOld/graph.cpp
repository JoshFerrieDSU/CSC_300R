#include "graph.h"

Graph::Graph(int maxV){
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;

    visted = new bool[maxVertices] {false}; //makes x new bools and sets them to false

    adjMatrix = new int*[maxVertices]; //pretty much array pointers
    for (int i = 0; i< maxVertices; i++){
        adjMatrix[i] = new int[maxVertices];
        for (int j = 0; j < maxVertices; i++){
            adjMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph(){
    delete[] visted;

    for (int i = 0; i< maxVertices; i++){
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    vertex* tempVertex;
    while (vertices) //via walking and pointers
    {
        edge* tempEdge;
        // free the memory of the neighbors
        while(vertices->aHead){
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->enext;
            delete tempEdge; //check
        }
        //free the vertex
        tempVertex = vertices;
        vertices = vertices->vnext;
        delete tempVertex;
    }

}

void Graph::addVertex(char data)
{
    if (numVertices >= maxVertices){
        cout<<"Filled up to the brim"<<endl;
        return;
    }
    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vnext = vertices;
    newVertex->aHead = nullptr;
    vertices = newVertex; //new head;
    numVertices++;
}