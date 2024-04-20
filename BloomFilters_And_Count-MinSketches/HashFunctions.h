/*
 * Name: CSE 100 Staff
 * Email: cs100sp22@ucsd.edu
 *
 * Sources Used: None.
 *
 * This file provides 5 hash functions that students need to use in their PA5.
 */

#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H
#include <functional>
#include <vector>
using namespace std;
extern const vector<function<unsigned int(const string &)>> hash_functions;
#endif
