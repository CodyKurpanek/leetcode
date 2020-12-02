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
#include<stack>
#include<queue>

using namespace std;

// A node for BST, doesn't need to store parent
class BSTNode{
    public:
        int value = -1;
        BSTNode *left = nullptr;
        BSTNode *right = nullptr;
        BSTNode(int value){
            this->value = value;
        }
};
//node for heap
class Node{
    public:
        int value = -1;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        Node(int value){
            this->value = value;
        }
};


//Binary Search Tree implementation
class BST{
    public:
        //instance variable
        BSTNode *root;
        //constructor
        BST(){
            root  = nullptr;
        }

        //Method to insert values into the BST beginning with the root.
        void insert(int value){
            BSTNode* tmp = new BSTNode(value);
            //rest of the code puts the node into the correct position
            //if no root yet
            if(root == nullptr){
                root = tmp;
                return;
            }
            BSTNode *current = root;
            //run through the rest of the bst, going in the correct direction until end of leaf
            while(1){            
                //if it should go to the left child
                if (value < current->value){
                    //if left is null, put new node there and method is finished otherwise go to that node
                    if(current->left == nullptr){
                        current->left = tmp;
                        return;
                    }
                    current = current->left;
                }
                //if it should go to the right child
                else{
                    //if right is null, put new node there and method is finished otherwise go to that node
                    if (current->right == nullptr){
                        current->right = tmp;
                        return;
                    }
                    current = current->right;
                }
            }
        }
        void deleteBST(){
            //if empty tree, return
            if (root == nullptr){
                return;
            }
            stack<BSTNode*> nodes;
            nodes.push(root);
            while(!nodes.empty()){
                BSTNode *tmp = nodes.top();
                nodes.pop();
                if (tmp->left != nullptr){
                    nodes.push(tmp->left);
                }
                if(tmp->right != nullptr){
                    nodes.push(tmp->right);
                }
                delete(tmp);
            }
            root = nullptr;
        }
};

//heap implementation
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
        //returns a pointer to the last node for insert and pop
        Node *lastNode(){
            if (finalLevelPosition % 2 == 0){
                if(finalCompleteLevel.at(finalLevelPosition / 2)->left == nullptr){
                    finalCompleteLevel.at(finalLevelPosition / 2)->left = new Node(0);
                    finalCompleteLevel.at(finalLevelPosition / 2)->left->parent =
                        finalCompleteLevel.at(finalLevelPosition / 2);
                }
                return finalCompleteLevel.at(finalLevelPosition / 2)->left;
            }
            else{
                if(finalCompleteLevel.at(finalLevelPosition / 2)->right == nullptr){
                    finalCompleteLevel.at(finalLevelPosition / 2)->right = new Node(0);
                    finalCompleteLevel.at(finalLevelPosition / 2)->right->parent =
                        finalCompleteLevel.at(finalLevelPosition / 2);
                }
                return finalCompleteLevel.at(finalLevelPosition / 2)->right;
            }
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
            //insert new item into the next open node, and save that node's current position
            Node* current = lastNode();
            current->value = value;
            //put the node further up into the heap until it is less than its parent's value
            while (current->parent != nullptr && current->parent->value < current->value){
                int tmp = current->parent->value;
                current->parent->value = current->value;
                current->value = tmp;
                current = current->parent;
            }
        }
        /*
        pops the maximum value. Does this by putting the last node's value into the root then
        moving that down throught the heap until it is in a place where it satisfies a heap 
        (parents > children). Checks the largest child when moving down.
        */

        int pop(){
            int top = root->value;
            //put the last node's value into root
            Node *current = lastNode();
            root->value = current->value;
            //delete the last node and set its parent's corresponding node to null
            if (finalLevelPosition % 2 == 1){
                current->parent->right = nullptr;
            }
            else{
                current->parent->left = nullptr;
            }
            delete(current);
            //rest of the method swithes current into the correct position
            current = root;
            Node* next;
            if(current->left->value > current->right->value){
                next = current->left;
            }
            else{
                next = current->right;
            }
            while(next->value > current->value){
                //swap next and current's value
                int tmp = next->value;
                next->value = current->value;
                current->value = tmp;
                //set current
                current = next;
                //set next
                if (current->left == nullptr && current->right == nullptr){
                    return top;
                }
                if(current->right == nullptr || (current->left->value > current->right->value)){
                    next = current->left;
                }
                else{
                    next = current->right;
                }
            }
            return top;
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
            root = nullptr;
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

void BFS(BST bst){
    //if empty tree, return
    if (bst.root == nullptr){
        return;
    }
    queue<BSTNode*> nodes;
    nodes.push(bst.root);
    while(!nodes.empty()){
        BSTNode *tmp = nodes.front();
        cout << tmp->value << " ";
        nodes.pop();
        if (tmp->left != nullptr){
            nodes.push(tmp->left);
        }
        if(tmp->right != nullptr){
            nodes.push(tmp->right);
        }
    }
    cout << endl;
}



int main(){
    BST bst;
    bst.insert(3);
    bst.insert(1);
    bst.insert(2);
    bst.insert(5);
    bst.insert(4);
    bst.insert(6);
    cout << "Breadth first search of tree:" << endl;
    BFS(bst);
    bst.deleteBST();

    bst.insert(3);
    bst.insert(6);
    bst.insert(5);
    bst.insert(4);
    bst.insert(2);
    bst.insert(3);

    cout << "Breadth first search of tree:" << endl;
    BFS(bst);
    bst.deleteBST();

    Heap heap;
    for(int i = 0; i < 10; i ++){
        heap.insert(i);
    }
    cout << "First 5 elements from the heap:" << endl;
    for(int i = 0; i < 5; i ++){
        cout << heap.pop() << " ";
    }
    heap.deleteHeap();

    return 0;
}

