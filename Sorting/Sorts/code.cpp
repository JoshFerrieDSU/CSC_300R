/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <iostream>

using namespace std;

void countingSort(int arr[], int n) {
    
    int max = 0;
    int i = 0;
    for (i = 0; i<=n; i++){ //find max
        if (arr[i] > max){
            max = arr[i];
        }
    }
    
    int sorted[max-1] = {}; //create array size of max
    for (i = 0; i<=max+1;i++){
        sorted[i] = sorted[i] + 1;
    }
    
    for (i = 0; i<=max+1;i++){
        cout<<i<<" frequency: "<<sorted[i]<<endl;
    }
    
    for (i = 0; i<=max+1;i++){
        cout<<i<<" frequency: "<<sorted[i]<<endl;
    }
    
}

int main()
{
    int array[8] = {4,4,4,3,2,6,2,1};
    countingSort(array, 8);
}