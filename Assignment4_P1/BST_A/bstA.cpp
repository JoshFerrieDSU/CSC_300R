#include "bstA.h"

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

void Queue::enqueue(int value) 
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

int Queue::dequeue() 
{
    int returning;
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

BST::BST(int size)
{
    capacity = size;
    tree = new int[capacity];
    for(int i = 0; i < size; i++)
        tree[i] = INT_MIN;
}

BST::~BST()
{
    delete[] tree;
}

int BST::leftChild(int index)
{
    return 2 * index + 1;
}

int BST::rightChild(int index)
{
    return 2 * index + 2;
}

int BST::parent(int index)
{
    return (index - 1) / 2;
}

void BST::insertI(int data)
{
    if(tree[0] == INT_MIN)
    {
        tree[0] = data;
        return;
    }

    int index = 0;

    while(index < capacity)
    {
        if(data < tree[index])
        {
            if(leftChild(index) < capacity && tree[leftChild(index)] == INT_MIN)
            {
                tree[leftChild(index)] = data;
                return;
            }
            index = leftChild(index);
        } else {
            if(rightChild(index) < capacity && tree[rightChild(index)] == INT_MIN)
            {
                tree[rightChild(index)] = data;
                return;
            }
            index = rightChild(index);
        }
    }
}

int max(int v1, int v2){
    if (v1>v2)
        return v1;
    else
        return v2;
}

int BST::height(int index){
    if (tree[index] == INT_MIN || index >= capacity){
        return 0;
    }
    int left = height(leftChild(index));
    int right = height(rightChild(index));
    int total = 1 + max(left, right); //note size does mess with this code not entirely sure the solution to this 
    cout<<"Height is: "<<total<<endl; //except for increasing the size. Maybe it has something to do with height
    return total;                       //and the fact that arrays have a limited size but more edges down = bigger size
    
}

int BST::countnodes(int index){ //depends on arr size like the other function above
    if (tree[index] == INT_MIN || index >= capacity){
        return 0;
    }
    int left = countnodes(leftChild(index));
    int right = countnodes(rightChild(index));
    int total = 1 + left + right;
    cout<<"counted: "<<total<<" so far"<<endl;
    return total;

}

bool BST::isbalanced(int index){
    if (tree[index] == INT_MIN || index >= capacity){
        return 0;
    }
    int lh = height(leftChild(index));
    int rh = height(rightChild(index));
    if (abs(lh-rh) > 1){
        cout<<"NOT BALANCED HEIGHT > 1"<<endl;
        //return false;
    }
    int rc = countnodes(rightChild(index));
    int lc = countnodes(leftChild(index));
    cout<<"Left Height: "<<lh<<endl<<"Right height: "<<rh<<endl<<"Rcount: "<<rc<<endl<<"Lcount"<<lc<<endl;
    if (rc>lc){
        cout<<"Right heavy"<<endl;
        return false;
    } else if(lc>rc){
        cout<<"Left heavy"<<endl;
        return false;
    } else{
        cout<<"Balanced"<<endl;
        return true;
    }
}

bool BST::hasleft(int index){
    if (tree[index] != INT_MIN){
        if (leftChild(index) <= capacity && tree[leftChild(index) != INT_MIN]){
            return true;
        }
    }
    return false;
}

bool BST::hasright(int index){
    if (tree[index] != INT_MIN){
        if (rightChild(index) <= capacity && tree[rightChild(index) != INT_MIN]){
            return true;
        }
    }
    return false;
}

int BST::minindex(int index){//for in order
    int current = index;
    while (leftChild(current) < capacity*2 && tree[leftChild(current)] != INT_MIN)
        current = leftChild(current);
    return current;
}

void BST::remove(int index){//couldnt figure this one out sadly, could we meet? josh.ferrie@trojans.dsu.edu
    if (index <= capacity && tree[index] != INT_MIN){
        bool right = hasright(index);
        bool left = hasleft(index);

        if (!right && !left){
            tree[index] = INT_MIN;
        }
        if (!right && left){
            tree[index] = tree[leftChild(index)];
            remove(tree[leftChild(index)]);
        }
        if (right && !left){
            tree[index] = tree[rightChild(index)];
            remove(rightChild(index));
        }

        //for 2 children
        if (right && left){
            int next = minindex(rightChild(index));
            tree[index] = tree[next];
            remove(next);
        }
        cout<<"Attempted to remove: "<<tree[index]<<endl;
    }
}

void BST::BFS(int index){
    if (tree[index] != INT_MIN){
        Queue queue;
        queue.enqueue(index);
        int current = index;
        while (queue.isEmpty() == false){
            current = queue.dequeue();
            cout<<"current is: "<<tree[current]<<endl;
            int lc = leftChild(current);
            int rc = rightChild(current);
            if (lc < capacity && tree[lc] != INT_MIN){
                queue.enqueue(lc);
            } 
            if (rc < capacity && tree[rc] != INT_MIN){
                queue.enqueue(rc);
            }
        }

    }
}

void BST::insertR(int data)
{
    insertRhelper(0, data);
}

void BST::insertRhelper(int index, int data)
{
    // Base case
    if(index >= capacity)
        return;
    if(tree[index] == INT_MIN)
    {
        tree[index] = data;
        return;
    }

    // Recursive case
    if (data < tree[index])
        insertRhelper(leftChild(index), data);
    else
        insertRhelper(rightChild(index), data);
}

bool BST::searchI(int data)
{
    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == INT_MIN)
            return false;
        if(tree[index] == data)
            return true;
        if(data < tree[index])
            index = leftChild(index); 
        else
            index = rightChild(index);
    }

    return false;
}

bool BST::searchR(int data)
{
    return searchRhelper(0, data);
}

bool BST::searchRhelper(int index, int data)
{
    // Base case
    if(index >= capacity || tree[index] == INT_MIN)
        return false;
    if(tree[index] == data)
        return true;

    // Recursive case
    if(data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

void BST::preorder(int index) // C-L-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}

void BST::inorder(int index) // L-C-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));
}

void BST::postorder(int index) // L-R-C
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    postorder(leftChild(index));
    postorder(rightChild(index));
    cout << tree[index] << " ";
}

void BST::printTree(int index, int depth = 0)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    
    printTree(rightChild(index), depth + 1);

    for(int i = 0; i < depth; i++)
        cout << "   "; // for indentation
    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
    
}