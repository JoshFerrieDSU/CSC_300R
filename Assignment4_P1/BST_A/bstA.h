#ifndef BSTA_H
#define BSTA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

struct qnode 
{
    int data;
    qnode* next;
    
    qnode(int value) 
    {
        data = value; 
        next = nullptr;
    }
};

class Queue 
{
    private:
        qnode* front;
        qnode* rear;
    public:
        Queue();
        ~Queue();
        int size = 0;
        
        void enqueue(int value);
        int dequeue();
        bool isEmpty();
        void display();
};


class BST
{
    private:
        int* tree;
        int capacity;

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

    public:
        BST(int size);
        ~BST();

        void insertI(int data);
        void insertR(int data);
        void insertRhelper(int index, int data);
        void remove(int index);

        bool hasright(int index);
        bool hasleft(int index);
        int minindex(int index);

        void BFS(int index);

        bool searchI(int data);
        bool searchR(int data);
        bool searchRhelper(int index, int data);

        int height(int index);
        int countnodes(int index);
        bool isbalanced(int index);

        void preorder(int index = 0);
        void inorder(int index = 0);
        void postorder(int index = 0);

        void printTree(int index, int depth);
};

#endif