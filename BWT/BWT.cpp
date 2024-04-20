/** 
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: 
 * https://rosettacode.org/wiki/Burrows%E2%80%93Wheeler_transform#C.2B.2B
 * I take this resource as reference for generating all cyclic rotatation
 * of input string
 * 
 * This file is the implementation of BWT.
 */
#include <string>
#include <vector>
#include <algorithm>
#include "BWT.h"
using namespace std;

/**
 * @brief doing BW-transformation of the given string by
 * sorting all its cyclic rotated strings and combining all
 * last elements of each rotated strings to form the result
 *  
 * @param s input string
 * @return string BWT result string
 */
string bwt(const string & s) {
    // BWT result string
    string s_bwt;
    // create string vector to collect all cyclic
    // rotated strings of s, including itself
    vector<string> BWTS(s.length());
    BWTS[0] = s;

    // generate all cyclic rotation 
    for(unsigned int i=0; i< s.length()-1;i++){
        char last = BWTS[i].back();
        string temp; 
        temp += last;
        temp += BWTS[i];
        temp.pop_back();
        BWTS[i+1] = temp;
    }
    // using in-built sort function to sort the collection
    sort(BWTS.begin(),BWTS.end());

    // generate the BWT result by concatenating the last char
    // of each rotated string
    for(string BWT: BWTS){
        s_bwt+= BWT.back();
    }

    return s_bwt;
}