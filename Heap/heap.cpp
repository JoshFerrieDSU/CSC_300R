#include "heap.h"

HEAP::HEAP(int size) {
    capacity = size;
    heapSize = 0;
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2*index + 1;
}
int HEAP::rightChild(int index) {
    return 2*index + 2;
}
int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert"<< endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while(index != 0 && array[parent(index)] < array[index]) {
        swap(array[parent(index)], array[index]);
        index = parent(index);
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    array[0] = array[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete"  << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    heapifyDown(index);
}


void HEAP::heapifyDown(int index) 
{
    while (true){
        int left = leftChild(index);
        int right = rightChild(index);
        int parent = index;

        if (left < heapSize && array[left] > array[parent]) //if in range and parent is LESS than left
        {
            parent = left;//set new max
        }

        if (right < heapSize && array[right] > array[parent])//in in range and parent is less than right
        {
            parent = right;//set new max
        }

        if (parent == index) //if parent = parent means nothing changed
        {
            break; //stop no need to continue and break the loop
        }

        swap(array[index], array[parent]); //helpful function that I never knew was in c so thanks
        index = parent;
    }
}

 
void HEAP::buildH(int arr[], int n) 
{
    if (n > capacity){//capacity check
        cout<<"TOO MUCH INPUT!"<<endl;
    }

    for (int i = 0; i< n; i++){
        array[i] = arr[i]; //set heap values from input
    }
    heapSize = n;//set size

    if (heapSize > 0){
        int start = parent(heapSize - 1); //start at last non leaf node
        for (int i = start; 0 <= i; i--){
            heapifyDown(i); //work your way up
        }
    }

    for (int i = 0; i<n; i++){
        arr[i] = array[i]; //finalize changes
    }


} 

void HEAP::replace(int oldData, int newData)
{
    int index = INT_MIN;

    for (int i = 0; i< heapSize; i++){
        if (array[i] == oldData){
            index = i;
            break; //go through list and find old data index
        }
    }

    if (index == INT_MIN)//no changes
    {
        cout<<"Cant replace, doesn't exist"<<endl;
        return;
    }

    int old = array[index];
    array[index] = newData; //replace

    if (newData > old){ //if value is larger then move it up if needed
        heapifyUp(index);
    } else if (newData < old){ //if value is smaller then move it down if needed
        heapifyDown(index);
    } //no need to consider equal
}

void HEAP::heapSort(int arr[], int n)//sort array using heap small to large
{
    if (n<=0){
        return;
    }

    HEAP temp(n);
    temp.buildH(arr, n);//make heap from array and it should sort it
    
    for (int i = n-1; 0 <= i; i--){
        int max = temp.peek();
        temp.deleteMax();
        arr[i] = max;
    }

    for (int i = 0; i<n; i++){
        cout <<arr[i]<<" ";
    }
    cout<<endl;
}

void HEAP::heapifyDownMin(int index){
    while (true){
        int left = leftChild(index);
        int right = rightChild(index);
        int parent = index; //min

        if (left < heapSize && array[left] < array[parent]) //if in range and parent is more than left
        {
            parent = left;//set new min
        }

        if (right < heapSize && array[right] < array[parent])//in in range and parent is more than right
        {
            parent = right;//set new min
        }

        if (parent == index) //if parent = parent means nothing changed
        {
            break; //stop no need to continue and break the loop
        }

        swap(array[index], array[parent]); //helpful function that I never knew was in c so thanks
        index = parent;
    }
}

void HEAP::switchMinMax(){
    if (heapSize <= 1){
        // if there is only less than 1 element then what's the point
        return;
    }

    int left = leftChild(0);
    int ismax = true;

    if (left < heapSize){
        if (array[0] < array[left]){
            ismax = false; // root is less than child
        }
    }

    int start = parent(heapSize - 1);
    if (ismax){ //if max heap then convert to min using hdm
        for (int i = start; 0 <= i; i--){
            heapifyDownMin(i); 
        }
    } else{ //if min heap then convert to max using old way
        for (int i = start; 0 <= 0; i--){
            heapifyDown(i);
        }
    }
}

void HEAP::printHeap(int index, int depth) {//old print wasn't working so I had it just print the array.
    if (index >= heapSize)
        return;

        for (int i = 0; i<=heapSize-1; i++){
            cout<<array[i]<<" ";
        }
        cout<<endl;
    // printHeap(rightChild(index), depth + 1);

    // for (int i = 0; i < depth; i++) {
    //     cout << "    "; // indentation based on depth
    // }

    // cout << array[index] << endl;

    // printHeap(leftChild(index), depth + 1);
}
