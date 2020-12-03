//Takes in values and puts them through a hash function. That hash function returns a number
//which is used as the index to an array. There are many ways of inserting multiple values
//whos hash functions both return the same number. I deal with it by creating a linked list
//at each array index, and making the nodes contain the key and value because at the node,
//you need to know if the value pertains to the same, nonhashed key

#include<iostream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

//Node for each element of the hash table
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

//exception for searching for a key that doesn't exist
class invalidKeyException: public exception{
    virtual const char* what() const throw(){
        return "Invalid Key";
    }
} invalidKeyException;



//Class to create a hash table
class hashTable{
    private:
        const static int HASHTABLESIZE = 26;
        Node* arr[HASHTABLESIZE];

        //hash function returns the alphabetical index of the first letter
        int hashFunction(string key){
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
        //insert into the hash table
        void insert(string key, int value){
            //Get the correct index of the hash table
            int arrIndex = hashFunction(key);
            Node *currentPosition = arr[arrIndex];
            //The rest of this method inserts into the next open spot of the linked list at the
            //correct index of the hash table
            //if first spot is open:
            if (currentPosition == nullptr){
                arr[arrIndex] = new Node(key, value);
            }
            //else, look through linked list until finding an index with the same key or next is null 
            else{
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
        //search for the value associated with a key
        int search(string key){
            //find correct index of hash table
            int arrIndex = hashFunction(key);
            Node *currentPosition = arr[arrIndex];
            //search the linked list at the correct index until finding a node with the same key
            while(currentPosition != nullptr){
                if (currentPosition->key == key){
                    return currentPosition->value;
                }
                currentPosition = currentPosition->next;
            }
            //if none of the same key is found, throw an invalicKeyException
            throw invalidKeyException;
        }

        //clear up the memory allocated to all of the nodes in the hash table
        void deleteTable(){
            //for all elements in the hash table
            for (unsigned int i = 0; i < HASHTABLESIZE; i ++){
                //delete all elements of the linked list at that index
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
    //insert the value 7 for the key four
    table.insert("four", 7);
    //create ten keys with the corresponding integer value
    const int amountOfValues = 10;    
    string keys[amountOfValues] = {"one", "two", "three", "four", "five", "six","seven", "eight",
     "nine", "ten"};
    int values[amountOfValues] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //insert all of them
    for(int i = 0; i < amountOfValues; i ++){
        table.insert(keys[i], values[i]);
    }
    try{
    cout << table.search("four") << " " << table.search("five") << endl;
    cout << table.search("six") << " " << table.search("seven") << endl;
    cout << table.search("hello") << endl;
    }catch(exception &e){
        cout << e.what() << endl;
    }
    
    table.deleteTable();
    return 0;
}