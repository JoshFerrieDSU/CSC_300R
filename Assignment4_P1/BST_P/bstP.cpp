#include "bstP.h"
///QUEUE

Queue::Queue()
{
    front = nullptr;
    rear = nullptr; 
}

Queue::~Queue() 
{
    while (!isEmpty()) 
    {
        dequeue();
    }
}

void Queue::enqueue(node* value) 
{
    qnode* newqnode = new qnode(value);

    if (isEmpty()){
        front = newqnode;
        rear = newqnode;
    } else{
        rear->next = newqnode;
        rear = newqnode;
    }
    size++;
}

node* Queue::dequeue() 
{
    node* returning;
    qnode* prev = front;
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

bool Queue::isEmpty() 
{
    return front == nullptr;
}

void Queue::display()
{
    qnode* current = front;
    cout << "Queue: ";
    
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}



//BST-P STUFF


node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }

    if(data < root->data)
        insertNode(root->leftChild, data);
    else 
        insertNode(root->rightChild, data);
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

int max(int v1, int v2){
    if (v1 < v2)
        return v2;
    else
    return v1;
}

int BST::height(node *root) //done
{
    if (root == nullptr){
        return 0;
    } else{
        int leftheight = height(root->leftChild);
        int rightheight = height(root->rightChild);
        int maximum = max(leftheight, rightheight);
        cout<<"Height is "<<maximum<<endl;
        return 1 + maximum;
    }
    
}

int BST::countnodes(node* root){ //done
    if (root == nullptr){
        return 0;
    }
    int leftnode = countnodes(root->leftChild);
    int rightnode = countnodes(root->rightChild);
    int total = 1 + leftnode + rightnode;
    cout<<"Counted "<<total<<" so far"<<endl;
    return 1 + leftnode + rightnode;
}

bool BST::isbalanced(node* root){
    if (root == nullptr){
        return false;
    }
    int leftnodes = BST::countnodes(root->leftChild);
    int rightnodes = BST::countnodes(root->rightChild);//account for nodes

    int lheight = BST::height(root->leftChild); //account for height
    int rheight = BST::height(root->rightChild);

    if (!(abs(lheight - rheight) <= 1)) //if height is not less than or equal to one then
        return false;
    if (leftnodes > rightnodes){
        cout<<"left heavy"<<endl;
        return false;
    } else if (rightnodes > leftnodes){
        cout<<"right heavy"<<endl;
        return false;
    } else{
        cout<<"balanced L: "<<leftnodes<<" r: "<<rightnodes<<endl;
        return true;
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::BFS(node* root) {
    if (root == nullptr){
        cout<<"Empty"<<endl;
    }
    else{
        Queue queue;
        queue.enqueue(root);
        node* current = root;

        while (queue.isEmpty() == false){
            current = queue.dequeue();
            cout<<"Current is: "<<current->data<<endl;
            if (current->leftChild != nullptr)
                queue.enqueue(current->leftChild);
            if (current->rightChild != nullptr){
                queue.enqueue(current->rightChild);
            }
            
        }
            

    }
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}


void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->leftChild, space);
}