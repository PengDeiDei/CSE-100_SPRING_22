/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: 
 * https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
 * I take this source as reference to write a lambda function for customized comparison
 * function inside a in-built sort() function.
 *  
 * This file is a header file to provide definition of suffix array
 */
#include <string>
#include <vector>
using namespace std;

/**
 * Construct the Suffix Array of a given string
 *
 * @param s The input string
 * @return A vector<unsigned int> representing the Suffix Array of s
 */
vector<unsigned int> suffix_array(const string & s);
