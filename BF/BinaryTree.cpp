// implement balanceFactors here, and don't forget to add proper styles.

#include "BinaryTree.h"
#include <queue>
#include <unordered_map>

unsigned int BinaryTree::depth(Node* node){
    if(node == nullptr){
        return 0;
    }else{
        return max(depth(node->leftChild),depth(node->rightChild))+1;    
    }
}

unordered_map<int,int> BinaryTree::balanceFactors(){
    queue<Node*> nodes{};
    unordered_map<int,int> BFs;

    if(this->root != nullptr){
        nodes.push(this->root);
    }else{
        return BFs;
    }

    while(!nodes.empty()){
            Node* curr = nodes.front();
            int leftHeight = depth(curr->leftChild);
            int rightHeight = depth(curr->rightChild);

            BFs[curr->label] = rightHeight - leftHeight;

            if(curr->leftChild != nullptr){
                nodes.push(curr->leftChild);
            }
            if(curr->rightChild != nullptr){
                nodes.push(curr->rightChild);
            }

            nodes.pop();
        }

    return BFs;
}
