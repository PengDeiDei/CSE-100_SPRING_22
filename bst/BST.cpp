/*
 * TODO: add a file header here.
 */
 /* 
    In PA2, I design the tree by follow the pseudocode on Stepik, below
    is the link of content of pseudocode:
    https://stepik.org/lesson/28727/step/4?unit=9785 
    https://stepik.org/lesson/28727/step/6?unit=9785
 */
#include "BST.h"
#include <vector>
#include <iostream>
BST::BST() { 
    root = nullptr;
    numElements = 0;
}

BST::~BST() {
    clear();
}

unsigned int BST::size() const {
    return numElements;
}

void BST::clear() {
    if(root == nullptr){
        return;
    }else{
        vector<Node*> nodes;
        nodes.push_back(root); 
        Node* curr = nullptr;
        while(!nodes.empty()){
            curr = nodes.front();
            nodes.pop_back();
            if(curr->leftChild != nullptr){
                nodes.push_back(curr->leftChild);
            }
            if(curr->rightChild != nullptr){
                nodes.push_back(curr->rightChild);
            }
            delete curr;
            numElements--;
        }
        root = nullptr;
    }
}

bool BST::insert(int element) {
    // create new node for root node if tree is empty
    Node* temp = new Node(element);
    if(root == nullptr){
        root = temp;
        numElements++;
        return true;
    }else{
        /* create a current node for looping trought tree
        if the left or right child is null, insert element as
        the related child of current node; otherwise, current
        node goes to next node. */
        Node* current = root;
        while(element != current->data){
            if(element < current->data){
                if(current->leftChild == nullptr){
                    temp->parent = current;
                    current->leftChild = temp;
                    numElements++;
                    return true;
                }else{
                    current = current->leftChild;
                }
            }else if(element > current->data){
                if(current->rightChild == nullptr){
                    temp->parent = current;
                    current->rightChild = temp;
                    numElements++;
                    return true;
                }else{
                    current = current->rightChild;
                }
            }
        }
        return false;
    }
}

bool BST::find(const int & query) const {
    if(root == nullptr){
        // return false if the tree is empty
        return false;
    }else{
        /* assign root node to a current node to loop through tree from root to 
        leaf, return true if find query, otherwise return false */
        Node* current = root;
        while(current != nullptr){
            if(query == current->data){
                return true;
            }else{
                // go to the left or right child by comparing query and data
                if(query > current->data){
                    current = current->rightChild;
                }else{
                    current = current->leftChild;
                }
            }
        }
        return false;
    }
}

BST::Node* BST::getLeftMostNode() {
    /* return the left most node or nullptr if tree is empty */
    if(root == nullptr){
        return nullptr;
    }
    Node* current = root;
    while(current->leftChild != nullptr){
        current = current->leftChild;   
    }
    return current;
}

BST::Node* BST::Node::successor() {
    /* YOUR CODE HERE */
    if(this->rightChild != nullptr){
        Node* current = this->rightChild;
        while(current->leftChild != nullptr){
            current = current->leftChild;
        }
        return current;
    }else{
        Node* current = this;
        while(current->parent != nullptr){
            if(current == current->parent->leftChild){
                return current->parent;
            }else{
                current = current->parent;
            }
        }
        return nullptr;
    }
}