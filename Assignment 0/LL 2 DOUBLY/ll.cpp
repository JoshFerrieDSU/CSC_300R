#include "ll.h"

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    if(index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while(walker != NULL && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            newNode->prev = walker;
            walker->next = newNode;
        }

    }
}

void deleteNode(node *&head, int index) 
{
    node* walker = head;    // Check if the list is empty and there's nothing to delete
    node* pwalker = head;
    if (head == nullptr){
        return;
    }
        // Write your code here!

    // Check if were are deleting at index 0 and handle accordingly
    if(index == 0)
    {

        head = walker->next;
        
        delete walker;
    }
    // Handle other index deletions
    else
    {
        int wIndex = 0;
        
        while (walker != NULL && wIndex <= index-1){ //loop that finds the prt at index
            walker = walker->next;
            wIndex++;
            cout<<"Index: "<<wIndex<<endl;
            if (wIndex == index-1){
                pwalker = walker;
            }
        }
        if (walker != nullptr){ //check if ptr exists
            pwalker->next = walker->next;
            walker->prev = pwalker;
            delete walker;
            //cout<<"deleted index: "<<wIndex<<endl;
        }

    }
}

void displayList(node *head) 
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;

}
