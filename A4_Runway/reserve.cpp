#include "reserve.h"

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr; 
}


BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(reservation* node)
{
    if (root == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// reserve new landing time
bool BST::reserve(int time) 
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }
 
    insert(root, time); 
    return true; // no conflict - reservation successful
}

// check for landing time conflicts within 3 minutes (Use recursion)
bool BST::checkConflict(reservation* node, int time) 
{
    if (node == nullptr){
        return false;
    } //no empty ptrs

    int dif = node->time - time; // time - node time aka
    if (dif < 0) {
        dif = -dif;
    } //aka abs(dif)

    cout<<"dif is: "<<dif<<endl;
    if (dif < 3){
        //cout<<"dif is: "<<dif<<endl;
        return true; //true is bad means conflict
    }
    bool conflict = checkConflict(node->left, time) || checkConflict(node->right, time); 
    return conflict; //false, then try right, or just no conflicts in general. any trues would show
} //recursively check the tree.

int subtreeSize(reservation* node){
    if (node == nullptr){
        return 0;
    }
    return 1 + subtreeSize(node->left) + subtreeSize(node->right);
}

// insert new reservation and update subtree size (make sure to avoid inserting duplicates)
void BST::insert(reservation*& node, int time) 
{
    cout<<"CALLED INSERT: "<<endl;
    if (node == nullptr) {
        node = new reservation(time);
        if (root == nullptr){
            root = node;
        }
        return;
    }

    if (time < node->time){//new time less than current node
        insert(node->left, time);
    } else if (time > node->time){
        insert(node->right, time);
    } else{
        return;
        //they are equal
    }

    node->subtreeSize = subtreeSize(node);
    cout<<subtreeSize<<endl;



    // same as before - just make sure to update subtree size for inserted node

    
}

// Count nodes with times <= t
//planes before or at t
int BST::countPlanes(reservation* node, int t) 
{
    if (node == nullptr){
        return 0;
    }

    if (t < node->time){//spam left until we get the first value that is less or equal to t
        return countPlanes(node->left, t);
    } else{ //all values less or equal to t
        return 1 + countPlanes(node->left,t) + countPlanes(node->right,t);
    }

}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;
    
    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}