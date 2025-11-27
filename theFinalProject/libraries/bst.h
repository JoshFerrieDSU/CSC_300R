struct bstnode
{
    int data;
    bstnode* leftChild;
    bstnode* rightChild;

    bstnode(int value){
        rightChild = nullptr;
        leftChild = nullptr;
        data = value;
    }
};

class BST
{
    public:
        bstnode* root;


BST()
{
    root = nullptr;
}

~BST()
{
    clearTree(root);
}

void clearTree(bstnode* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

void insertNode(bstnode*& root, int data)
{
    if(root == nullptr)
    {
        root = new bstnode(data);
        return;
    }

    if(data < root->data)
        insertNode(root->leftChild, data);
    else 
        insertNode(root->rightChild, data);
}

bstnode* searchNode(bstnode*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void deleteNode(bstnode*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            bstnode* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            bstnode* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            bstnode* temp = root->rightChild;
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

int height(bstnode *root) //done
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

int countnodes(bstnode* root){ //done
    if (root == nullptr){
        return 0;
    }
    int leftnode = countnodes(root->leftChild);
    int rightnode = countnodes(root->rightChild);
    int total = 1 + leftnode + rightnode;
    cout<<"Counted "<<total<<" so far"<<endl;
    return 1 + leftnode + rightnode;
}

bool isbalanced(bstnode* root){
    if (root == nullptr){
        return false;
    }
    int leftnodes = countnodes(root->leftChild);
    int rightnodes = countnodes(root->rightChild);//account for nodes

    int lheight = height(root->leftChild); //account for height
    int rheight = height(root->rightChild);

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

void preorder(bstnode* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}
};

