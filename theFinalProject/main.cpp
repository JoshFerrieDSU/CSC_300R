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
    bool usingrandomset = true; //false = using values specified above, true = generate x random values from terminal input when ran ex /.a 20.
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
        cout<<"["<<index<<"]"<<": "<<walker->data<<endl;
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
    int goalIndex = rand()%(amountofrandomvalues-2) + 1;//generates values from [1] to [maxindex-1]
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

    goalValue = workingset[6];

    cout<<"Stack:\nTrying to locate ["<<goalValue<<"] at "<< 6<<endl;

    for (int i = 0; s.isEmpty() == false; i++){
        int value = s.pop();
        if (value == goalValue){
            cout<<"Found matching value in stack layer "<<i<<endl;
        } else{
            if (i % (amountofrandomvalues/10) == 0 )
                cout<<"------"<<i<<"------\n";
        }
    }

    timer.endAndPrint();
//----------------------------------------------------------------------------------

    //queue area
    timer.startTimer();
    Queue q;
    

    //insert

    //find max

    //find min

    //find [6]

    //end timer
    timer.endAndPrint();

//----------------------------------------------------------------------------------

    timer.startTimer();
    //bst area -start timer

    //insert

    //find max

    //find min

    //find [6]

    //end timer
    timer.endAndPrint();


    timer.printHistory();
}