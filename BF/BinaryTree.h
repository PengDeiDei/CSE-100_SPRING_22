/*
 * Name: CSE 100 Staff
 * Email: cs100sp22@ucsd.edu
 *
 * Sources Used: None.
 *
 * This file is a header file for CSE 100 PA3 in Spring 2022.
 * It provides a definition for a Binary (not necessary Search) Tree. Students
 * will need to implement balanceFactors in BinaryTree.cpp
 */


#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;
const char NEWICK_SEPARATOR = ',';
const char NEWICK_START = '(';
const char NEWICK_END = ')';
const char NEWICK_TERMINATOR = ';';
const string LEFT_CHILD_MISMATCH =
        "'s left-child's parent node does not link to itself.";
const string RIGHT_CHILD_MISMATCH =
        "'s right-child's parent node does not link to itself.";
const string DUPLICATE_LABEL =
        "the tree contains nodes with duplicate labels: ";

/**
 * Class to implement an binary tree
 */
class BinaryTree {
public:
    /**
     * Nested helper Node class. It keeps track of the references to the
     * left/right child and the parent, and its label.
     */
    class Node {
    public:
        /**
         * The label of this node
         */
        int label;

        /**
         * Pointer to the node's left child
         */
        Node *leftChild;

        /**
         * Pointer to the node's right child
         */
        Node *rightChild;

        /**
         * Pointer to the node's parent
         */
        Node *parent;

        /**
         * Node constructor, which initializes the label and set everything else
         * to nullptr
         */
        Node(int x) : label(x), leftChild(nullptr), rightChild(nullptr),
                      parent(nullptr) {}

        /**
         * Print the Newick string of the subtree rooted at this node to
         * standard error
         */
        void newick() {
            if (this->leftChild == nullptr && this->rightChild == nullptr) {
                cerr << this->label;
                return;
            }
            cerr << NEWICK_START;
            if (this->leftChild) {
                this->leftChild->newick();
                if (this->rightChild) {
                    cerr << NEWICK_SEPARATOR;
                }
            }
            if (this->rightChild) {
                this->rightChild->newick();
            }
            cerr << NEWICK_END << this->label;
        }
    };

    /**
     * Construct a new tree based on an existing tree structure.
     *
     * @param root root node
     */
    BinaryTree(Node *root) {
        queue<Node *> nodes{};
        unordered_set<int> labels;
        if (root != nullptr) {
            nodes.push(root);
        }

        while (!nodes.empty()) {
            // no duplicate labels are allowed.
            auto node = nodes.front();
            if (labels.find(node->label) == labels.end()) {
                labels.insert(node->label);
            } else {
                throw invalid_argument(
                        DUPLICATE_LABEL + to_string(node->label));
            }

            // references are all set correctly.
            if (node->leftChild != nullptr) {
                if (node->leftChild->parent != node) {
                    throw invalid_argument(
                            to_string(node->label) + LEFT_CHILD_MISMATCH);
                }
                nodes.push(node->leftChild);
            }

            if (node->rightChild != nullptr) {
                if (node->rightChild->parent != node) {
                    throw invalid_argument(
                            to_string(node->label) + RIGHT_CHILD_MISMATCH);
                }
                nodes.push(node->rightChild);
            }
            nodes.pop();
        }

        this->root = root;
    }

    /**
     * Print the Newick string representing this tree to standard error
     */
    void newick() {
        if (this->root) {
            this->root->newick();
            cerr << NEWICK_TERMINATOR << endl;
        }
    }

    /**
     * Calculate the balance factors for the current tree.
     *
     * @return an unordered_map mapping node labels to balance factors,
     * where "balance factor" is defined as right height minus left height
     *
     * For example, in the following binary tree:
     *
     *         (1)
     *        /   \
     *      (2)    (6)
     *     /   \
     *   (5)   (3)
     *            \
     *            (4)
     *
     * You would return an unordered_map bf with the following (key, value)
     * pairs:
     *     - bf[1] =  -2 because the balance factor of node 1 is 1 - 3 = -2
     *     - bf[2] =  1 because the balance factor of node 2 is 2 - 1 =  1
     *     - bf[3] =  1 because the balance factor of node 3 is 1 - 0 =  1
     *     - bf[4] =  0 because the balance factor of node 4 is 0 - 0 =  0
     *     - bf[5] =  0 because the balance factor of node 5 is 0 - 0 =  0
     *     - bf[6] =  0 because the balance factor of node 6 is 0 - 0 =  0
     */
    unordered_map<int, int> balanceFactors();
    unsigned int depth(Node* node);

private:
    /**
     * Pointer to the root node of this binary tree
     */
    Node *root;
};

#endif
