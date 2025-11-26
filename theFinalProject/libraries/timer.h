#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
//#include <ctime>

class Timer
{
    public:
        bool running = false;
        bool hasRan = false;
        clock_t start;
        clock_t end;
        int difference;
        
        Queue q;//using queue for history
        

        double getDifference(){
            return end-start;
        }
        void startTimer(){
            start = clock();
            running = true;
            if (hasRan == false){
                hasRan = true;
            }
        }
        void endTimer(){
            if (running == true){
                end = clock();
                difference = getDifference()*1000 / 1000000*CLOCKS_PER_SEC;
                running = false;
                q.enqueue(difference);
            }
        }
        void printTimer(){
            if (hasRan == true){
                if (start <= end){
                    cout<<"Time length: "<<difference<<" ms\n";
                } else{
                    cout<<"Time length: Currently Running\n";
                }
            }
        }
        void endAndPrint(){
            endTimer();
            printTimer();
        }
        void printHistory(){
            for (int i = 0; q.isEmpty() == false; i++){
                cout<<"["<<i<<"]: "<<q.dequeue()<<" ms\n";
            }
        }
};