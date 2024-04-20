/*
 * Name: Niema Moshiri (modified by Qingyang for Spring 2022)
 * Email: niema@ucsd.edu
 *
 * Sources Used: None.
 *
 * This file is a tester file for CSE 100 in Spring 2022.
 * It tests whether getLeftMostNode and successor have the correct
 * implementation.
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <string>
#include "BST.h"
using namespace std;

/**
 * Define messages for use in the tester
 */
const string MESSAGE_SUCCESS = "Success";
const string MESSAGE_INCORRECT = "Your successor() function returned the "
    "wrong node";
const string MESSAGE_PREMATURE_NULL = "Your successor() function returned "
    "NULL too early";
const string MESSAGE_NOT_NULL_AT_END = "Your successor() function was not "
    "NULL when we expected it to be (at the end)";
const string MESSAGE_INCORRECT_LEFTMOST_EMPTY = "Your getLeftMostNode() "
    "function did not return NULL on an empty BST";
const int TEST_SIZE = 100;
const int DATA_RANGE = 10000;
const int DATA_OFFSET = 5000;

/**
 * Test BST class using numbers from standard input
 */
int main() {
    // randomly sample a bunch of integers
    BST bst;
    if(bst.getLeftMostNode() != nullptr) {
        cout << MESSAGE_INCORRECT_LEFTMOST_EMPTY << endl;
        return 1;
    }
    srand(time(NULL));
    set<int> nums;
    while(nums.size() < TEST_SIZE) {
        int num = (rand() % DATA_RANGE) - DATA_OFFSET;
        nums.insert(num);
        bst.insert(num);
    }

    // test successor
    BST::Node* curr = bst.getLeftMostNode();
    for(int num : nums) {
        if(curr == nullptr) {
            cout << MESSAGE_PREMATURE_NULL << endl;
            return 1;
        }
        if(curr->data != num) {
            cout << MESSAGE_INCORRECT << endl;
            return 1;
        }
        curr = curr->successor();
    }
    if(curr != nullptr) {
        cout << MESSAGE_NOT_NULL_AT_END << endl;
        return 1;
    }

    // if it didn't fail yet, success!
    cout << MESSAGE_SUCCESS << endl;
    return 0;
}
