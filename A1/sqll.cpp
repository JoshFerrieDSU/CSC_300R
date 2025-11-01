#include "sqll.h"

//======================= STACK ===========================

Stack::Stack()
{
    top = nullptr; 
}

Stack::~Stack() 
{
    while (!isEmpty()) 
    {
        pop();
    }
}

void Stack::push(string& value) 
{
    node* prev = top; 
    node* newnode = new node(value);
    top = newnode;
    newnode->next = prev; //even works if empty
    //cout<<"pushed "<<value<<" to stack"<<endl;
}

string Stack::pop() 
{
    node* prev = top;
    string rdata = "";
    if (isEmpty()) 
    {
        throw runtime_error("Stack is empty");
    } else{
        rdata = prev->data;
        top = top->next;
        delete top;
    }

    return rdata;
}

string Stack::peek() 
{
    if (isEmpty()) 
    {
        throw runtime_error("Stack is empty");
    }

    return top->data;  
}

bool Stack::isEmpty() 
{
    return top == nullptr;
}

void Stack::display()
{
    node* current = top;
    cout << "Stack: ";
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//======================= QUEUE ===========================

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

void Queue::enqueue(string& value) 
{
    node* newnode = new node(value);

    if (isEmpty()){
        front = newnode;
        rear = newnode;
    } else{
        rear->next = newnode;
        rear = newnode;
    }
    size++;
}

string Queue::dequeue() 
{
    string returning = "";
    node* prev = front;
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
    node* current = front;
    cout << "Queue: ";
    
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
//======================= DIJKSTRA'S TWO STACK ===========================
double evaluateExpression(string& expr) 
{
    double returning = 0;
    Stack operands;
    Stack operators;
    int len = 0;
    int i = 0;
    char current;
    bool lastdigit = false;
    string nbuilder;
    
    if (expr.empty() == false){
        len = expr.length();
        for (i = 0; i<len; i++){
            current = expr[i];
            string converter(1, current);
            if (isdigit(current)){
                nbuilder=nbuilder+current;
                lastdigit = true;
                //
            } else if (current != ' '){
                if (lastdigit == true){
                    operands.push(nbuilder);
                    nbuilder = "";
                }
                if (current == '+' || current == '-' || current == '*' || current == '/'){
                    operators.push(converter);
                    lastdigit = false;
                    //
                } else if (current == ')'){
                    lastdigit = false;
                    int o1 = stoi(operands.pop());
                    int o2 = stoi(operands.pop());
                    string operman = operators.pop();
                    int result = 0;
                    string sresult;
                    
                    switch(operman[0]){
                        case '+':
                            result = o1+o2;
                            sresult = to_string(result);
                            operands.push(sresult);
                            break;
                        case '-':
                            result = o2-o1;
                            sresult = to_string(result);
                            operands.push(sresult);
                            break;
                        case '*':
                            result = o2*o1;
                            sresult = to_string(result);
                            operands.push(sresult);
                            break;
                        case '/':
                            result = o2/o1;
                            sresult = to_string(result);
                            operands.push(sresult);
                            break;
                        default:
                            cout<<"Unknown char"<<endl;
                    }
                    
                    cout<<o1<<operman<<o2<<"="<<result<<endl;
                    returning = result;
                }
            }
            
        }
    }
    
    return returning;
}

// ============= JOSEPHUS PROBLEM ===========================
void josephus(int n, int k) 
{
    Queue queue; //get n people, every kth person is killed
    Queue alive;
    int i = 0;


    for (i=1; i<=n; i++){
        string converter = to_string(i);
        queue.enqueue(converter);
    } //1 to n;

    queue.display();
    cout<<"Size: "<<queue.size<<endl;
    while (queue.size > 1){

        int antiover = (k-1)%queue.size; //prevents overflowing

        for (int i = 0; i<antiover; i++){//skips k important
            string val = queue.dequeue();
            alive.enqueue(val);
        }
        string deleting = queue.dequeue();
        cout<<"person "<<deleting<<" eliminated"<<endl;
        
        while (alive.size > 0){//move everything back
            string val = alive.dequeue();
            queue.enqueue(val); 
        }

    }
    string winner = queue.dequeue();
    cout<<"LAST PERSON REMAINING IS: "<<winner<<endl;


}