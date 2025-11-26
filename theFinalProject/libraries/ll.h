#include <iostream>

using namespace std;

struct lnode //linked list
{
    int data;
    struct lnode *next;
};

void insertNode(lnode *&head, int index, int data)
{
    lnode* newNode = new lnode;
    newNode->data = data;
    newNode->next = nullptr; 

    if(index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        lnode* walker = head;
        int wIndex = 0;
        while(walker != nullptr && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            //cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next = newNode;
        }

    }
}



void deleteNode(lnode *&head, int index) 
{
    lnode* walker = head;    // Check if the list is empty and there's nothing to delete
    lnode* pwalker = head;
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
        
        while (walker != nullptr && wIndex <= index-1){ //loop that finds the prt at index
            walker = walker->next;
            wIndex++;
            cout<<"Index: "<<wIndex<<endl;
            if (wIndex == index-1){
                pwalker = walker;
            }
        }
        if (walker != nullptr){ //check if ptr exists
            pwalker->next = walker->next;
            delete walker;
            //cout<<"deleted index: "<<wIndex<<endl;
        }

    }
}

lnode* searchNode(lnode *head, int key){ //Dont think the datatype of search node was specificed so i have it return the pointer and print location.
    int wIndex = 0; //ignore that i just read the menu lol
    lnode* walker = head;
        
        while (walker != nullptr){
            if (walker->data == key){
                cout<<"Index: "<<wIndex<<endl;
                return walker;
            }
            walker = walker->next;
            wIndex++;
        }
        return walker;
}

lnode* reverseList(lnode *head){
    int wIndex = 0;
    lnode* pwalker = nullptr; //previous 
    lnode* cwalker = head; //current
    lnode* nwalker = nullptr; //next

    while (cwalker != nullptr){
        nwalker = cwalker->next;
        cwalker->next = pwalker;

        pwalker = cwalker;
        cwalker = nwalker;


    }

    return pwalker;
}


void displayList(lnode *head) 
{
    lnode* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;

}