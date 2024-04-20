/*
 * Name: CSE 100 Staff
 * Email: cs100sp22@ucsd.edu
 *
 * Sources Used: None.
 *
 * This file is a tester file for CSE 100 PA3 in Spring 2022.
 * It tests whether balanceFactors returns the correct map for the example tree
 * given in the BinaryTree.h file.
 */

/* Macro to explicity print tests that are run along with colorized result. */
#define TEST(EX) (void)((fprintf(stdout, "(%s:%d) %s:", __FILE__, __LINE__,\
                 #EX)) && ((EX && fprintf(stdout, "\t\x1b[32mPASSED\x1b[0m\n"))\
                 || (fprintf(stdout, "\t\x1b[31mFAILED\x1b[0m\n")) ))

#include "BinaryTree.h"

typedef BinaryTree::Node Node;

/**
 * Test the example tree in the BinaryTree.h file.
 */
void testExampleTree1() {
    Node *node1 = new Node(1);
    Node *node2 = new Node(2);
    node2->parent = node1;
    node1->leftChild = node2;

    Node *node6 = new Node(6);
    node6->parent = node1;
    node1->rightChild = node6;

    Node *node5 = new Node(5);
    node5->parent = node2;
    node2->leftChild = node5;

    Node *node3 = new Node(3);
    node3->parent = node2;
    node2->rightChild = node3;

    Node *node4 = new Node(4);
    node4->parent = node3;
    node3->rightChild = node4;

    auto tree = BinaryTree(node1);
    auto factors = tree.balanceFactors();
    for (auto pair: factors) {
        cout << pair.first << '\t'<< pair.second << endl;
    }

    tree.newick();

    TEST(factors.size() == 6);
    TEST(factors[1] == -2);
    TEST(factors[2] == 1);
    TEST(factors[3] == 1);
    TEST(factors[4] == 0);
    TEST(factors[5] == 0);
    TEST(factors[6] == 0);
}

void testExampleTree2() {
    /*  Perfectly balanced
     *           (4)
     *        /       \
     *     (2)         (6)
     *    /   \       /   \
     *  (1)   (3)   (5)   (7)
     */

    Node *node4 = new Node(4);
    Node *node2 = new Node(2);
    node2->parent = node4;
    node4->leftChild = node2;

    Node *node6 = new Node(6);
    node6->parent = node4;
    node4->rightChild = node6;

    Node *node1 = new Node(1);
    node1->parent = node2;
    node2->leftChild = node1;

    Node *node3 = new Node(3);
    node3->parent = node2;
    node2->rightChild = node3;

    Node *node5 = new Node(5);
    node5->parent = node6;
    node6->leftChild = node5;

    Node *node7 = new Node(7);
    node7->parent = node6;
    node6->rightChild = node7;

    auto tree = BinaryTree(node4);
    auto factors = tree.balanceFactors();
    cout<< factors.size()<<endl;
    for (auto pair: factors) {
        cout << pair.first << '\t'<< pair.second << endl;
    }

    tree.newick();

    TEST(factors.size() == 7);
    TEST(factors[1] == 0);
    TEST(factors[2] == 0);
    TEST(factors[3] == 0);
    TEST(factors[4] == 0);
    TEST(factors[5] == 0);
    TEST(factors[6] == 0);
    TEST(factors[7] == 0);
}

void testExampleTree3() {
    /* Perfectly unbalanced
     *(1)
     *  \
     *  (2)
     *    \     
     *    (4)
     *      \
     *      (6)
     *      /
     *    (5)
     */

    Node *node1 = new Node(1);
    Node *node2 = new Node(2);
    node2->parent = node1;
    node1->rightChild = node2;

    Node *node4 = new Node(4);
    node4->parent = node2;
    node2->rightChild = node4;

    Node *node6 = new Node(6);
    node6->parent = node4;
    node4->rightChild = node6;

    Node *node5 = new Node(5);
    node5->parent = node6;
    node6->leftChild = node5;

    auto tree = BinaryTree(node1);
    auto factors = tree.balanceFactors();
    cout<< factors.size()<<endl;
    for (auto pair: factors) {
        cout << pair.first << '\t'<< pair.second << endl;
    }

    tree.newick();

    TEST(factors.size() == 5);
    TEST(factors[1] == 4);
    TEST(factors[2] == 3);
    TEST(factors[5] == 0);
    TEST(factors[4] == 2);
    TEST(factors[6] == -1);
}

void testExampleTree4() {
    /* One Node
     *      (1)
     */

    Node *node1 = new Node(1);

    auto tree = BinaryTree(node1);
    auto factors = tree.balanceFactors();
    cout<< factors.size()<<endl;
    for (auto pair: factors) {
        cout << pair.first << '\t'<< pair.second << endl;
    }

    tree.newick();

    TEST(factors.size() == 1);
    TEST(factors[1] == 0);
}

void testExampleTree5() {
    /* Empty
     */

    auto tree = BinaryTree(nullptr);
    auto factors = tree.balanceFactors();
    for (auto pair: factors) {
        cout << pair.first << '\t'<< pair.second << endl;
    }

    tree.newick();

    TEST(factors.size() == 0);
}

void testExampleTree6() {
    /*  AVL Tree
     *           (4)
     *         /     \
     *       (2)      (6)
     *         \      /
     *         (3)  (5)
     */

    Node *node4 = new Node(4);
    Node *node2 = new Node(2);
    node2->parent = node4;
    node4->leftChild = node2;

    Node *node6 = new Node(6);
    node6->parent = node4;
    node4->rightChild = node6;

    Node *node3 = new Node(3);
    node3->parent = node2;
    node2->rightChild = node3;

    Node *node5 = new Node(5);
    node5->parent = node6;
    node6->leftChild = node5;

    auto tree = BinaryTree(node4);
    auto factors = tree.balanceFactors();
    cout<< factors.size()<<endl;
    for (auto pair: factors) {
        cout << pair.first << '\t'<< pair.second << endl;
    }

    tree.newick();

    TEST(factors.size() ==5);
    TEST(factors[2] == 1);
    TEST(factors[3] == 0);
    TEST(factors[4] == 0);
    TEST(factors[5] == 0);
    TEST(factors[6] == -1);
}

/**
 * Run our test cases.
 */
int main() {
    //testExampleTree1();
    //testExampleTree2();
    //testExampleTree3();
    //testExampleTree4();
    //testExampleTree5();
    testExampleTree6();
    return 0;
}

