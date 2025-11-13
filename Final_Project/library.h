//make heap, bst, linked list, and array
//Only need to make a heap, probably a max heap
//Goal is to fill everything up with the same random set of values, then see which ones can find a min, max, and a middle value.
#ifndef FINAL_H
#define FINAL_H

#include <iostream>
using namespace std;

struct lnode
{
    int data;
    struct lnode *next;
};



void insertNode(lnode *&head, int index, int data);
void deleteNode(lnode *&head, int index);
void displayList(lnode *head);
lnode* searchNode(lnode *head, int key);
lnode* reverseList(lnode *head);

//for pointer bsts
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

struct bstnode
{
    int data;
    bstnode* leftChild;
    bstnode* rightChild;

    bstnode(int value);
};

struct qnode 
{
    bstnode* data;
    qnode* next;
    
    qnode(bstnode* value) 
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
        
        void enqueue(bstnode* value);
        bstnode* dequeue();
        bool isEmpty();
        void display();
};

class BST
{
    public:
        bstnode* root;

        BST();
        ~BST();
        void clearTree(bstnode* node);

        void insertNode(bstnode*& root, int data);
        bstnode* searchNode(bstnode*& root, int data);
        void deleteNode(bstnode*& root, int data);
        int height(bstnode* root);
        int countnodes(bstnode* root);
        bool isbalanced(bstnode* root);
        void BFS(bstnode* root);

        void preorder(bstnode* root);
        void inorder(bstnode* root);
        void postorder(bstnode* root);

        void printTree(bstnode* root, int space);
};

#endif