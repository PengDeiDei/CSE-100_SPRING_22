/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: 
 * https://stackoverflow.com/questions/37368787/c-sort-one-vector-based-on-another-one
 * I take this source as reference to write a lambda function for customized comparison
 * function inside a in-built sort() function.
 *  
 * This file is the implemetation of constructing a suffix array.
 */
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include "SuffixArray.h"

using namespace std;

/**
 * @brief construct a suffix array by given string
 * 
 * @param s input string 
 * @return vector<unsigned int> the constructed suffix array
 *  of s
 */
vector<unsigned int> suffix_array(const string & s) {
    // create suffix array and assign indices to it
    vector<unsigned int> indices(s.length());
    for(unsigned i=0; i<s.length();i++){
        indices[i] = i;
    }

    // convert string s to C-string for substring comparison
    // while avoiding using .substr() function
    const char* s_cstr = s.c_str();

    // sort suffix array by doing comparison of suffix substrings 
    // of s; 
    // inside the sort function, I implement a lambda function
    // as customized comparsion function
    sort(indices.begin(),indices.end(),
        [&](unsigned int a, unsigned int b)->bool{
            return strcmp(s_cstr+a, s_cstr+b)<0;
        });
    return indices;   
}
