#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

using namespace std;

struct edge
{
    vertex* dest;
    edge* enext;

    int weight;
};

struct vertex
{
    char data;
    vertex* vnext;
    edge* aHead; //linked list start for its children/neighbors
};

class Graph
{
    private:
        vertex* vertices; //list of vertices
        int** adjMatrix;
        bool* visted;
        int maxVertices;
        int numVertices;

    public:
        Graph(int maxV);
        ~Graph();

        //core operations

        void addVertex(char data);
        void addEdge(char src, char dest, int weight);
        void removeVertex(char data);
        void removeEdge(char src, char dest);

        //traversal algorithms
        void bfsL(char start);
        void bfsM(char start);
        void dfsL(char start);
        void dfsM(char start);

        // display
        void displayList();
        void displayMatrix();

};

#endif