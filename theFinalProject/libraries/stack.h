#include <iostream>

class Stack 
{
    private:
        node* top;
    public:
        Stack()
        {
            top = nullptr; 
        }

        ~Stack() 
        {
            while (!isEmpty()) 
            {
                pop();
            }
        }

        void push(int value) 
        {
            node* prev = top; 
            node* newnode = new node(value);
            top = newnode;
            newnode->next = prev; //even works if empty
            //cout<<"pushed "<<value<<" to stack"<<endl;
        }

        int pop() 
        {
            node* prev = top;
            int rdata = 0;
            if (isEmpty()) 
            {
                throw runtime_error("Stack is empty");
            } else{
                rdata = prev->data;
                top = top->next;
                delete prev;
            }

            return rdata;
        }

        int peek() 
        {
            if (isEmpty()) 
            {
                throw runtime_error("Stack is empty");
            }

            return top->data;  
        }

        bool isEmpty() 
        {
            return top == nullptr;
        }

        void display()
        {
            node* current = top;
            cout << "Stack: ";
            while (current != nullptr) 
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};