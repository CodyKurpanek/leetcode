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
        Node *root = nullptr;

        //constructor
        BST(){
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




int main(){
    BST tree;
    Node *a = createNode(4);
    tree.insert(4);
    tree.insert(2);

    cout << tree.root->value << endl;
}

