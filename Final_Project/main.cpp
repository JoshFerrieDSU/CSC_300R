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
//try to grab index [6] = 62




int main (int argc, char *argv[])
{
    int amountofrandomvalues = stoi(argv[1]);// this is x
    int workingset[amountofrandomvalues];
    bool usingrandomset = true; //false = using values specified above, true = generate x random values.
    if (usingrandomset){
        srand(20); //generate same set of random numbers
        for (int i = 0; i<amountofrandomvalues;i++){
            workingset[i] = rand()%1000000; //0-999999
        }
    }
//----------------------------------------------------------------------------------


    Timer timer;

    //linked list area - start time
    timer.startTimer();
    lnode* head = nullptr;
    lnode* tList = nullptr;

    if (usingrandomset == true){
        for (int i = 0; i<amountofrandomvalues; i++){
            insertNode(head, i, workingset[i]);
        }
    } else{
        for (int i = 0; i<13; i++){
            
            insertNode(head, 0, 6);
            insertNode(head, 1, 5);
            insertNode(head, 2, 4);
            insertNode(head, 3, 23);
            insertNode(head, 4, 51);
            insertNode(head, 5, 25);
            insertNode(head, 6, 62);
            insertNode(head, 7, 1);
            insertNode(head, 8, 36);
            insertNode(head, 9, 263);
            insertNode(head, 10, 1993);
            insertNode(head, 11, 3);
            insertNode(head, 12, 91);
        }
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

    //stack area

    //insert

    //find max

    //find min

    //find [6]

//----------------------------------------------------------------------------------

    //queue area
    Queue q;
    

    //insert

    //find max

    //find min

    //find [6]

    //end timer

//----------------------------------------------------------------------------------

    //bst area -start timer

    //insert

    //find max

    //find min

    //find [6]

    //end timer



}