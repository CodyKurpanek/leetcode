//Resizable array of objects; usually created much larger than needed so push_back
//can be used. When they run out of space, a new larger one is recreated in memory

#include <iostream>
#include <vector>

using namespace std;


//print all elements of the vector. Using a pointer to save time and space; a new
//vector is not created whenever the function is called.
void printElementsInVector(vector<int>* arr){
    for (vector<int>::iterator it = arr->begin(); it < arr->end(); it ++){
        cout << *it << " ";
    }
    cout << endl;
}


//methods of creating a vector with elements:
void MethodsOfCreatingAVector(int method){
    //when you don't know what values are in the vector
    if (method == 0){
        vector<int> vect;
        vect.push_back(1);
        vect.push_back(2);
        vect.push_back(3);
    }
    //When you want a certain amount of elements all initialized to a value
    if (method == 1){
        int numElements = 3, elementValue = 0;
        vector<int> vect(numElements, elementValue);
    }
    //when you know exactly what to initialize the vector to
    if (method == 2){
        vector<int> vect = {1, 2, 3};    
    }
    //from an array
    if (method == 3){
        int arr[3] = {1, 2, 3};
        vector<int> values(arr, arr + sizeof(arr) / sizeof(int));
    } 
    //part of a vector or structure with an iterator
    if (method == 4){
        vector<int> oldVector = {0, 1, 2, 3};
        vector<int> newVector(oldVector.begin() + 1, oldVector.end());
        printElementsInVector(&newVector);
        printElementsInVector(&oldVector);
    }
}


int main(){
    MethodsOfCreatingAVector(4);
}