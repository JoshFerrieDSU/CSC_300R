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

void HEAP:: switchMinMax(){
    
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
    // complete this
}

 
void HEAP::buildH(int arr[], int n) 
{
    // complete this
}

void HEAP::replace(int oldData, int newData)
{
    // complete this
}

void HEAP::heapSort(int arr[], int n)
{
    // complete this
}

void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; // indentation based on depth
    }

    cout << array[index] << endl;

    printHeap(leftChild(index), depth + 1);
}
