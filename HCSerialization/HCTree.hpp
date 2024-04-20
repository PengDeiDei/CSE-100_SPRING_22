/*
 * Name: CSE 100 Staff
 * Email: cs100sp22@ucsd.edu
 *
 * Sources Used: 
 * https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree
 * This source provides a good reference of implementing serilization on 
 * huffman tree
 *
 * This file provides a skeleton for a huffman tree. For students, feel free
 * to implement the tree in HCTree.cpp (you can create a new file).
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP
#include <queue>
#include <vector>
#include <fstream>
#include "Helper.hpp"
using namespace std;

/**
 * A Huffman Code Tree class
 */
class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;
    unsigned int symbols_size; // total number of unique symbols in tree
    /**
     * @brief Recursively serialize the HC tree and write the sequence of encoded bits and 
     * char of symbols to the given FancyOutputStream as the header of compressed
     * file
     * 
     * PRECONDITION: build() has been called, to create the coding tree,
     *               and initialize root pointer and leaves vector.
     * 
     * @param curr HCNode ptr to serialize the leaves of tree
     * @param out output stream for the serialized bits
     */
    void serial_recur(HCNode* curr, FancyOutputStream & out) const;

    /**
     * @brief Recursively deserilize the endoced HC tree and reconstruct 
     * the tree with only its architecture and symbols
     * 
     * @param index index of bits in the file header 
     * @param len length of the file header
     * @param in input stream to find encoded bits
     * 
     * @return HCNode* reconstructed node of HC tree
     */
    HCNode* deserial_recur(FancyInputStream & in, int & index, int len) const;

public:
    /**
     * Constructor, which initializes everything to null pointers
     */
    HCTree() : root(nullptr) {
        leaves = vector<HCNode*>(256, nullptr);
    }

    /**
    * @brief Destroy the HCTree::HCTree object
    * 
    */
    ~HCTree();

    /**
     * Use the Huffman algorithm to build a Huffman coding tree.
     * PRECONDITION:  freqs is a vector of ints, such that freqs[i] is the
     *                frequency of occurrence of byte i in the input file.
     * POSTCONDITION: root points to the root of the trie, and leaves[i]
     *                points to the leaf node containing byte i.
     *
     * @param freqs frequency vector
     * 
     */
    void build(const vector<int>& freqs);

    /**
     * Write to the given FancyOutputStream the sequence of bits coding the
     * given symbol.
     * PRECONDITION: build() has been called, to create the coding tree,
     *               and initialize root pointer and leaves vector.
     *
     * @param symbol symbol to encode
     * @param out output stream for the encoded bits
     */
    void encode(unsigned char symbol, FancyOutputStream & out) const;

    /**
     * Return symbol coded in the next sequence of bits from the stream.
     * PRECONDITION: build() has been called, to create the coding tree, and
     *               initialize root pointer and leaves vector.
     *
     * @param in input stream to find encoded bits
     * @return a single char decoded from the input stream
     */
    unsigned char decode(FancyInputStream & in) const;

    /**
     * @brief Warpper for private function serial_recur 
     * 
     * @param out output stream for the serialized bits
     */
    void serial(FancyOutputStream & out) const;


};
#endif // HCTREE_HPP
