#include "library.h"

//max, min, random
//find ll max, min, random
//find heap max min random
//find bst max min random
//find array max min random



//goal is to build the data stucture with the same inputs. We will use
//6, 5, 4, 23, 51, 25, 62, 1, 36, 263, 1993, 3, 91
//min is at [7]
//13 numbers
//max at [10]
//try to grab random index excluding the ends rand()%(maxindex-2)+1




int main (int argc, char *argv[])
{
    bool usingrandomset = argc >= 2; //false = using values specified above, true = generate x random values from terminal input when ran ex /.a 20.
    int amountofrandomvalues = usingrandomset ? stoi(argv[1]) : 13;// this is x
    int workingset[amountofrandomvalues];
    
    if (usingrandomset){
        srand(20); //generate same set of random numbers
        for (int i = 0; i<amountofrandomvalues;i++){
            workingset[i] = rand()%1000000; //0-999999
        }
    } else{
        workingset[0] = 6;
        workingset[1] = 5;
        workingset[2] = 4;
        workingset[3] = 23;
        workingset[4] = 51;
        workingset[5] = 25;
        workingset[6] = 62;
        workingset[7] = 1;
        workingset[8] = 36;
        workingset[9] = 263;
        workingset[10] = 1993;
        workingset[11] = 3;
        workingset[12] = 91;
    }
//----------------------------------------------------------------------------------


    Timer timer;

    //linked list area - start time
    timer.startTimer();
    lnode* head = nullptr;
    lnode* tList = nullptr;


    for (int i = 0; i<amountofrandomvalues; i++){
        insertNode(head, i, workingset[i]);
    }

    //find max will be in linear time since it has to iterate through the whole list
    int max = INT_MIN;
    lnode* walker = head;
    int index = 0;
    int maxindex = 0;
    while (walker != nullptr){
        // cout<<"["<<index<<"]"<<": "<<walker->data<<endl;
        int value = walker->data;
        if (value > max){
            max = value;
            maxindex = index;
        }
        walker = walker->next;
        index++;
    }
    cout<<"Maximum for LL ["<<maxindex<<"] is: "<<max<<endl;

    //find min linear time
    int min = INT_MAX;
    walker = head;
    index = 0;
    int minindex = 0;
    while (walker != nullptr){
        //cout<<"["<<index<<"]"<<": "<<walker->data<<endl;
        int value = walker->data;
        if (value < min){
            min = value;
            minindex = index;
        }
        walker = walker->next;
        index++;
    }
    cout<<"Minimum for LL ["<<minindex<<"] is: "<<min<<endl;
    

    //find [6] little less than linear time if found before last index
    index = 0;
    srand(time(NULL));
    int goalIndex = amountofrandomvalues >= 3 ? rand()%(amountofrandomvalues-2) + 1 : rand()%amountofrandomvalues;;//generates values from [1] to [maxindex-1] otherwise nothing
    int randomGenerated = goalIndex;
    int goalValue = INT_MIN;
    walker = head;
    while (walker != nullptr && goalValue == INT_MIN){
        int value = walker->data;
        if (index == goalIndex){
            goalValue = value;
        }
        index++;
        walker = walker->next;
    }
    if (goalValue != INT_MIN){
        cout<<"["<<goalIndex<<"] = "<<goalValue<<endl;
    } else{
        cout<<"Index "<<goalIndex<<" could not be found.\n";
    }



    //show time - end ll
    timer.endAndPrint();

//----------------------------------------------------------------------------------

    timer.startTimer();
    //stack area
    Stack s;
    Stack sBackup;
    //insert
    for (int i = 0; i<amountofrandomvalues; i++){
        s.push(workingset[i]);
    }

    //find max
    max = INT_MIN;
    for (int i = 0; s.isEmpty() == false; i++){
        int value = s.pop();
        sBackup.push(value);

        if (max < value){
            max = value;
        }
    }
    while (sBackup.isEmpty() == false){//rebuild from backup
        s.push(sBackup.pop());
    }
    cout<<"Maximum for stack: "<<max<<endl;



    //find min
    min = INT_MAX;
    for (int i = 0; s.isEmpty() == false; i++){
        int value = s.pop();
        sBackup.push(value);

        if (min > value){
            min = value;
        }
    }
    while (sBackup.isEmpty() == false){
        s.push(sBackup.pop());
    }
    cout<<"Minimum for stack: "<<min<<endl;

    //find value at workingset[6] since stack doesn't keep track of indexes well

    goalValue = workingset[randomGenerated];

    cout<<"Trying to locate "<<goalValue<<" at index "<< 6<<endl;

    for (int i = 0; s.isEmpty() == false; i++){
        int value = s.pop();
        int nozero = amountofrandomvalues > 14 ? amountofrandomvalues/14 : 1; //if input larger than 14 then input/14 otherwise 1
        if (i % nozero == 0 ){
            //cout<<"------"<<i<<"------\n";
        }   
        if (value == goalValue){
            cout<<"Found ["<<value<<"] value in stack layer "<<i<<endl;
             break;
        } else{
        }
    }

    timer.endAndPrint();
//----------------------------------------------------------------------------------

    //queue area
    timer.startTimer();
    Queue q;
    Queue qBackup;

    //insert
    for (int i = 0; i<amountofrandomvalues; i++){
        q.enqueue(workingset[i]);
    }

    //find max
    max = INT_MIN;
    while (q.isEmpty() == false){
        int value = q.dequeue();
        qBackup.enqueue(value);
        if (value > max){
            max = value;
        }
    }
    while (qBackup.isEmpty() == false){
        int value = qBackup.dequeue();
        q.enqueue(value);
    }
    cout<<"Queue max: "<<max<<endl;
    //find min
    min = INT_MAX;
    while (q.isEmpty() == false){
        int value = q.dequeue();
        qBackup.enqueue(value);
        if (value < min){
            min = value;
        }
    }
    while (qBackup.isEmpty() == false){
        int value = qBackup.dequeue();
        q.enqueue(value);
    }
    cout<<"Queue min: "<<min<<endl;

    //find [6]
    goalValue = workingset[goalIndex];
    while (q.isEmpty() == false){
        int value = q.dequeue();
        if (value == goalValue){
            cout<<"Queue found random value: "<<value<<endl;
            break;
        }
    }

    //end timer
    timer.endAndPrint();

//----------------------------------------------------------------------------------

    timer.startTimer();
    //bst area -start timer
    BST bst;

    //insert
    for (int i = 0; i<amountofrandomvalues; i++){
        bst.insertNode(bst.root, workingset[i]);
    }

    //find max
    max = INT_MIN;
    for (bstnode* bstwalker = bst.root; bstwalker != nullptr; bstwalker = bstwalker->rightChild){
        max = bstwalker->data;
    }
    cout<<"BST max: "<<max<<endl;

    //find min

    max = INT_MAX;
    for (bstnode* bstwalker = bst.root; bstwalker != nullptr; bstwalker = bstwalker->leftChild){
        max = bstwalker->data;
    }
    cout<<"BST min: "<<min<<endl;

    //find [6]

    bstnode* bstwalker = bst.root;
    goalValue = workingset[goalIndex];
    while(bstwalker != nullptr){
        int value = bstwalker->data;
        if (value == goalValue){
            cout<<"BST found "<<value<<endl;
            break;
        } else if (value > goalValue){
            bstwalker = bstwalker->leftChild;
        } else{ //if current is smaller
            bstwalker = bstwalker->rightChild;
        }
    }

    //end timer
    timer.endAndPrint();


    timer.printHistory();
}