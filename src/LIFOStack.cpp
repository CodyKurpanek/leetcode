//Stacks are a data structure such that the Last element added to the data structure is accessible
//meaning it can be viewed or popped.
//methods are empty, size, top, push, emplace, pop, and swap.

//To implement in code, #include <stack>

#include <iostream>

using namespace std;


//Nodes to be used in my implementation of a stack
class Node{
    public:
        int value;
        Node *previous = nullptr;
    public:
        Node(int value){
            this->value = value;
        }
};


//Implement an integer stack that has all of the functionality of the one 
//in the standard namespace except for swap
class Stack{
    private:
        //attributes. Edit both when working with methods
        //Note: since methods will be named size and top, those names are reserved and 
        //the attributes need to be given different names hence size1 and top1.
        int size1 = 0;
        Node* top1 = nullptr;
    public:
        //methods
        bool empty(){
            if (this->size1 == 0){
                return true;
            }
            return false;
        }
        void push(int value){
            if(empty()){
                top1 = new Node(value);
            }
            else{
                Node *previous = top1;
                top1 = new Node(value);
                top1->previous = previous;
            }
            ++size1;
        }
        //Emplace is different than push because it calls the object's constructor on the 
        //inputted value. Not very helpful for integer stack because ints are a basic datatype
        void emplace(int inputValue){
            //create an integer using the integer constructor
            int value(inputValue);

            if(empty()){
                top1 = new Node(value);
            }
            else{
                Node *previous = top1;
                top1 = new Node(value);
                top1->previous = previous;
            }
            ++size1;
        }
        int pop(){
            if (empty()){
                return -1;
            }
            //save values from the popped element that will be needed later
            int returnValue = top1->value;
            Node* top = top1;
            //pop the element
            top1 = top1->previous;
            // clear the memory allocated for the popped element
            delete(top);

            --size1;
            return returnValue;
        }
        int top(){
            return top1->value;
        }
        int size(){
            return size1;
        }
};

int main(){
    //Test the stack class by using all of the methods. Comments keep track of the current stack.

    Stack numbers;
    numbers.emplace(2);
    //numbers:  2
    numbers.emplace(3);
    //numbers: 2 3
    cout << numbers.top() << " should print 3" << endl;
    cout << numbers.pop() << " should print 3" << endl; 
    //numbers: 2
    numbers.push(4);
    //numbers: 2 4
    cout << numbers.size() << " should print 2" << endl;
    cout << numbers.top() << " should print 4" << endl;
    cout << numbers.pop() << " should print 4" << endl;
    //numbers: 2
    cout << numbers.empty() << " should print 0" << endl;
    cout << numbers.pop() << " should print 2" << endl;
    //numbers:
    cout << numbers.empty() << " should print 1" << endl;

}