#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

struct node
{
    int data;
    node* leftChild;
    node* rightChild;

    node(int value);
};

struct qnode 
{
    node* data;
    qnode* next;
    
    qnode(node* value) 
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
        
        void enqueue(node* value);
        node* dequeue();
        bool isEmpty();
        void display();
};

class BST
{
    public:
        node* root;

        BST();
        ~BST();
        void clearTree(node* node);

        void insertNode(node*& root, int data);
        node* searchNode(node*& root, int data);
        void deleteNode(node*& root, int data);
        int height(node* root);
        int countnodes(node* root);
        bool isbalanced(node* root);
        void BFS(node* root);

        void preorder(node* root);
        void inorder(node* root);
        void postorder(node* root);

        void printTree(node* root, int space);
};

#endif