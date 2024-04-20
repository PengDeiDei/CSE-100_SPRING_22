/*
 * Name: CSE 100 Staff
 * Email: cs100sp22@ucsd.edu
 *
 * Sources Used: None.
 *
 * This file provides 5 hash functions that students need to use in their PA5.
 */

#include <functional>
#include <string>
#include <vector>
#include "HashFunctions.h"

using namespace std;

const int SHIFT_1 = 13;
const int SHIFT_2 = 17;

/**
 * Hash function 1 (please read the method to understand the detailed hashing
 * implementation).
 * @param s string to hash
 * @return hash value of the string
 */
unsigned int h1(const string &s) {
    unsigned int o = 0;
    for (const char &c: s) {
        o += c;
    }
    return o;
}

/**
 * Hash function 2 (please read the method to understand the detailed hashing
 * implementation).
 * @param s string to hash
 * @return hash value of the string
 */
unsigned int h2(const string &s) {
    unsigned int o = 0;
    for (const char &c: s) {
        o = (SHIFT_1 * o) + c;
    }
    return o;
}

/**
 * Hash function 3 (please read the method to understand the detailed hashing
 * implementation).
 * @param s string to hash
 * @return hash value of the string
 */
unsigned int h3(const string &s) {
    unsigned int o = 0;
    for (const char &c: s) {
        o = (SHIFT_2 * o) + c;
    }
    return o;
}

/**
 * Hash function 4 (please read the method to understand the detailed hashing
 * implementation).
 * @param s string to hash
 * @return hash value of the string
 */
unsigned int h4(const string &s) {
    unsigned int o = 0;
    for (const char &c: s) {
        o = (SHIFT_2 * o) + c;
        if (o > SHIFT_1) {
            o -= SHIFT_1;
        }
    }
    return o;
}

/**
 * Hash function 5 (please read the method to understand the detailed hashing
 * implementation).
 * @param s string to hash
 * @return hash value of the string
 */
unsigned int h5(const string &s) {
    return s.size();
}

const vector <function<unsigned int(const string &)>> hash_functions
        {h1, h2, h3, h4, h5};
