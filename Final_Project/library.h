//make queue, bst, linked list, and stack
//Goal is to fill everything up with the same random set of values, then see which ones can find a min, max, and a middle value.
#ifndef FINAL_H
#define FINAL_H

#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>


#include <iostream>
using namespace std;

struct lnode //linked list
{
    int data;
    struct lnode *next;
};



void insertNode(lnode *&head, int index, int data);
void deleteNode(lnode *&head, int index);
void displayList(lnode *head);
lnode* searchNode(lnode *head, int key);
lnode* reverseList(lnode *head);

//end ll

//for pointer bsts

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

class Timer
{
    public:
        bool running = false;
        bool hasRan = false;
        clock_t start;
        clock_t end;
        int difference;
        
        Queue q;
        

        double getDifference(){
            return double(end-start);
        }
        void startTimer(){
            start = clock();
            running = true;
            if (hasRan == false){
                hasRan = true;
            }
        }
        void endTimer(){
            if (!running)
                return;
            end = clock();
            difference = getDifference()*1000 / 1000000*CLOCKS_PER_SEC;
            running = false;
        }
        void printTimer(){
            if (hasRan == true){
                if (start < end){
                    cout<<"Time length: "<<difference<<" ms\n";
                } else{
                    cout<<"Time length: Currently Running\n";
                }
            }
        }
        void endAndPrint(){
            endTimer();
            printTimer();
        }
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