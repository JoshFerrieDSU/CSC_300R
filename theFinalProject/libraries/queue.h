#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

struct node 
{
    int data;
    node* next;
    
    node(int value) 
    {
        data = value; 
        next = nullptr;
    }
};

class Queue 
{
    private:
        node* front;
        node* rear;
    public:
        int size = 0;
        
        Queue()
        {
            front = nullptr;
            rear = nullptr; 
        }

        ~Queue() 
        {
            while (!isEmpty()) 
            {
                dequeue();
            }
        }

        void enqueue(int& value) 
        {
            node* newnode = new node(value);

            if (isEmpty()){
                front = newnode;
                rear = newnode;
            } else{
                rear->next = newnode;
                rear = newnode;
            }
            size++;
        }

        int dequeue() 
        {
            int returning = 0;
            node* prev = front;
            prev = front;

            if (isEmpty()){
                throw runtime_error("Queue is empty...");
            } else{
                returning = prev->data;
                front = front->next;
                delete prev;
            }
            size--;
            return returning;
        }

        bool isEmpty() 
        {
            return front == nullptr;
        }

        void display()
        {
            node* current = front;
            cout << "Queue: ";
            
            while (current != nullptr) 
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};