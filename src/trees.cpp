/*
A tree is a loose datastrucute where nodes are connected to other nodes by edges. No node's
child can be the root node, and they are generally acyclical.

Terminology includes: 
    parent, the node that points the current node
    child, a node that the current node points to
    leaf, a node that has no child nodes, at the end of the tree
    root, the node that has no parents, at the beginning of the tree
    Subtree, the tree created by the ascendents of a node with that node as the root
    visiting, checking the value of a node
    traversing, Going down nodes in a specific path
    levels, the generation of a node. If the root node is at level 0, its children are at 1
    keys, the value that is accessed from a specific node
    binary tree, a tree who's parent nodes have two children nodes, one to the left and one to the right


A main type of tree is a binary search tree. for a binary search tree, the value of the child to 
the left is a smaller value, and the one on the right is a larger value. BSTs typically
 dont have duplicate values, but there are certain methods of dealing with duplicates.

Therefore, the next closest node may not be the next value in order, but it is always greater
or less in value; 10 could have a child to the right with 12 whos child to the left is 11.


A heap is a binary tree in which every node's children contain lower values. The root, therefore,
holds the maximum value and is accessed often.

*/

#include<iostream>
#include<vector>

using namespace std;

// A node for a tree
class Node{
    public:
        int value = -1;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int value){
            this->value = value;
        }
};

//Binary Search Tree implementation
class BST{
    public:
        //instance variable
        Node *root;

        //constructor
        BST(){
            root  = nullptr;
        }

        //Method to insert values into the BST beginning with the root.
        void insert(int value){
            Node a(value);
            /*
            TODO: initialize the nodes into memory in the heap (with new)

            in the first run, instance.insert(4), it sets root to a node at 0x61fe80 with value 4
            //in the second run, instance.insert(2), changes 0x61fe80's value to 2.
            //THE MEMORY FOR VARIABLES ON THE STACK IS CLEARED UP FOR ANY NEW VARIABLES TO USE
            //AFTER LEAVING THIS METHOD. ANY VARIABLES THAT NEED TO BE SAVED AFTER ABANDONING
            //A SCOPE NEED TO BE SAVED IN THE HEAP.
            */


            //rest of the code puts the node into the correct position
            if(root == nullptr){
                root = &a;
                //cout << "4?" << root ->value << endl;
                return;
            }
            cout << root -> value;
            Node *current = root;
            while(1){            
                //if it should go to the left child
                if (value < current->value){
                    if(current -> left == nullptr){
                        current -> left = &a;
                        return;
                    }
                }
                //if it should go to the right child
                else{
                    //TODO complete code for if the value is greater than at the current node
                    return;
                    
                }
            }
        }
};


class Heap{
    public:
        Node *root;
        //the final completed level; used for finding the last node. Used in insertion and getMax.
        vector<Node*> finalCompleteLevel;
        //the last empty spot on the level after the final level; also used to find the last node.
        //say finalCompleteLevel is a one level below the root and has two nodes. In that case, 
        //finalPosition = 0 refers to the left child of the first node, finalPosition = 1 refers
        //to the right node of child one, finalPosition = 2 refers to the left node of the second
        //child, and finalPosition = 3 refers to the right child of the node at the second position.
        int finalLevelPosition;

        Heap(){
            root = nullptr;
        }

        //if the level after finalCompleteLevel is completed, call repopulate to change 
        //finalCompleteLevel to that level. 
        void repopulateFinalCompleteLevel(){
            vector<Node *> newFinalCompleteLevel;
            for (int i = 0; i < finalCompleteLevel.size(); i ++){
                newFinalCompleteLevel.push_back(finalCompleteLevel.at(i)->left);
                newFinalCompleteLevel.push_back(finalCompleteLevel.at(i)->right);
                finalLevelPosition = -1;
            }
            finalCompleteLevel = newFinalCompleteLevel;
        }
        //insert a value into the heap
        void insert(int value){
            if (root == nullptr){
                root = new Node(value);
                finalCompleteLevel.push_back(root);
                finalLevelPosition = -1;
                return;
            }
            int maxIndex = ((finalCompleteLevel.size() * 2) - 1);
            //If the next row has been fully populated, switch to next row
            if (finalLevelPosition >= maxIndex){
                repopulateFinalCompleteLevel();
            }
            //increment up to the next open node
            finalLevelPosition++;
            //insert new item into the next open node
            if (finalLevelPosition % 2 == 0){
                finalCompleteLevel.at(finalLevelPosition / 2)->left = new Node(value);
            }
            else{
                finalCompleteLevel.at(finalLevelPosition / 2)->left = new Node(value);
            }
            //TODO put the node into the correct position of the heap

            //TODO void getmax();

        }
        // 2 following methods delete the entire heap and deallocate all of the memory
        //First called by outside methods
        void deleteHeap(){
            //recursively delete the children of root until the children don't exist
            if(root->left != nullptr){
                deleteHeap(root->left);
            }
            if(root->right != nullptr){
                deleteHeap(root->right);
            }
            delete(root);
        }
    private:
        //called by the deleteHeap without arguments for subsequent children.
        void deleteHeap(Node* parent){
            //recursively delete the children of root until the children don't exist
            if(parent->left != nullptr){
                deleteHeap(parent->left);
            }
            if(parent->right != nullptr){
                deleteHeap(parent->right);
            }
            delete(parent);
        }
};


int main(){
    Heap heap;
    heap.insert(2);
    heap.insert(4);
    heap.insert(3);
    heap.deleteHeap();

    return 0;
}

