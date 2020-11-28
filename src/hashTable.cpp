//Takes in values and puts them through a hash function. That hash function returns a number
//which is used as the index to an array. There are many ways of inserting multiple values
//whos hash functions both return the same number. I deal with it by creating a linked list
//at each array index, and making the nodes contain the key and value because at the node,
//you need to know if the value pertains to the same, nonhashed key

//note to self: understand static. Change so that insert can be done with brackets.
//understand exception processing

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Node{
    public:
        int value;
        string key;
        Node *next;
        Node(string key, int value){
            this->value = value;
            this->key = key;
            next = nullptr;
        }
};



//Class to create a hash table
class hashTable{
    private:
        const static int HASHTABLESIZE = 26;
        Node* arr[HASHTABLESIZE];
        
        //my hash function returns the alphabetical index of the first letter
        int hashValue(string key){
            unsigned int returnVal = key.at(0) - 'a';
            return (returnVal);
        }
    public:
        //how many indices are in the hash table. Don't know why but has to be static
        hashTable(){
            for(unsigned int i = 0; i < HASHTABLESIZE; i++){
                arr[i] = nullptr;
            }
        }
        //insert into the hash table with key and value
        void insert(string key, int value){
            int arrIndex = hashValue(key);
            Node *currentPosition = arr[arrIndex];
            
            if (currentPosition == nullptr){
                arr[arrIndex] = new Node(key, value);
            }
            else{
                //maybe I can change this to somethign different than while(1)
                while (1){
                    if(currentPosition->key == key){
                        currentPosition->value = value;
                        return;
                    }
                    if(currentPosition->next == nullptr){
                        currentPosition->next = new Node(key, value);
                        return;
                    }
                    currentPosition = currentPosition->next;
                }
            }
        }
        int getValue(string key){
            int arrIndex = hashValue(key);
            Node *currentPosition = arr[arrIndex];
            while(currentPosition != nullptr){
                if (currentPosition->key == key){
                    return currentPosition->value;
                }
                currentPosition = currentPosition->next;
            }
            cout << "INVALID KEY" << endl;
            throw 1;
        }
        //clear up the memory allocated to all of the nodes in the hash table
        void deleteTable(){
            for (unsigned int i = 0; i < HASHTABLESIZE; i ++){
                Node* currentPosition = arr[i];
                while(currentPosition != nullptr){
                    Node* tmp = currentPosition;
                    currentPosition = currentPosition->next;
                    delete(tmp);
                }
            }
        }

};

int main(){
    hashTable table;

    const int amountOfValues = 10;
    string keys[amountOfValues] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    int values[amountOfValues] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i = 0; i < amountOfValues; i ++){
        table.insert(keys[i], values[i]);
    }
    cout << table.getValue("four") << " " << table.getValue("five") << endl;

    table.deleteTable();

    return 0;
}