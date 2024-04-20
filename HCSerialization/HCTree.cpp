/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: https://www.techiedelight.com/huffman-coding/
 * I took this source as reference for Huffman Tree
 *  
 * This file provides functions for a huffman tree. 
 */
#include "HCTree.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <fstream>
#include <bitset>
#include "Helper.hpp"
using namespace std;

HCTree::~HCTree(){
    // return if tree is empty
    if(root == nullptr){
        return;
    }else{
        // using queue to continuously pop out the first node stored in it,
        // and stores its children back until all the nodes are deleted 
        queue<HCNode*> nodes;
        HCNode* curr = nullptr;
        nodes.push(root);
        while(!nodes.empty()){
            curr = nodes.front();
            nodes.pop();
            if(curr->c0 != nullptr){
                nodes.push(curr->c0);
            }
            if(curr->c1 != nullptr){
                nodes.push(curr->c1);
            }
            delete curr;
        }
        // root node should be reserved but asigned it as nullptr
        root = nullptr;
    }
}

void HCTree::build(const vector<int>& freqs){
    symbols_size = 0;
    // using priority queue to construct the HC tree
    priority_queue <HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    for(unsigned int i = 0; i < freqs.size(); i++){
        if(freqs[i] > 0){
            symbols_size++;
            HCNode* newNode = new HCNode(freqs[i],i);
            // store new node into the look-up vector and pq
            leaves[i] = newNode;
            pq.push(newNode);
        }
    }

    // follow the algorithm of HC tree to merge the first two nodes with lowest
    // frequencies in the pq as a new node and store it back to the pq. 
    while(pq.size()>1){
        HCNode* left = pq.top(); pq.pop();
        HCNode* right = pq.top(); pq.pop();
        // the symbol of new merged node is null to implement serialization later if
        // possible
        HCNode* combined  = new HCNode(left->count+right->count,'\0');
        left->p = combined; right->p = combined;
        combined->c0 = left; combined->c1 = right;
        pq.push(combined);
    }
    // root node is the pnly element stored in the pq once the tree is built up
    root = pq.top();
    pq.pop(); // empty the pq
}

// The precondition indicates that this function will only be called 
// once the build() function is called to build up the HC tree. 
// Root node should always be not null when calling this function
void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
    // find the node with specific symbol from the look-up vector
    HCNode* curr = leaves[symbol];
    stack <int> bits;
    bits.push(1);
    while(curr != root){
        // encode the symbol in little-endian order
        bits.push(0);
        curr = curr->p; 
    }
    while(!bits.empty()){
        out.write_bit(bits.top());
        bits.pop();
    }
}

// The precondition indicates that this function will only be called 
// once the build() function is called to build up the HC tree. 
// Root node should always be not null when calling this function
unsigned char HCTree::decode(FancyInputStream & in) const{
    int bit = -1;
    HCNode* curr = root;
    // the while loop is terminated if reaches a leaf of tree
    while(!(curr->c0 == nullptr && curr->c1 == nullptr)){
        // get the LSB
        bit = in.read_bit();
        if(bit == 0){ // go to left
            if(curr->c0 != nullptr){
                curr = curr->c0;
            }else{ // reach the leaf
                return curr->symbol;
            }
        }else{// go to right
            if(curr->c1 != nullptr){
                curr = curr->c1;
            }else{ //reach the leaf
                return curr->symbol;
            }
        }
    }
    // this return should not be reached if the
    // implementation is correct
    return curr->symbol;
}

// wrapper function to prevent directly using root node 
void HCTree::serial(FancyOutputStream & out) const{
    out.write<unsigned short>(symbols_size);
    serial_recur(root, out);
}

void HCTree::serial_recur(HCNode* curr, FancyOutputStream & out) const{
    if(curr == nullptr){
        return;
    }
    // Once reach the leaf nodes, write bit 1.
    // Then convert the symbol of node to 8 bits,
    // and write them into stream.
    if(curr->c0 == nullptr && curr->c1 == nullptr){
        out.write_bit(1);
        bitset<8> sym_bits = curr->symbol;
        for(unsigned int i = 0; i < 8; i++){
            out.write_bit(sym_bits[7-i]);
        }
    }else{
        // Reach internal nodes, write bit 0
        out.write_bit(0);

        // using recursion to go further
        serial_recur(curr->c0, out);
        serial_recur(curr->c1, out);
    }
}

HCNode* HCTree::deserial_recur(FancyInputStream & in, int & index, int len) const{
    if(index >= len){
        return nullptr;
    }

    return nullptr;
}
