/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: Stepik CH 5.10.
 *
 * This file provides the interface for a count-min sketch.
 */
#include <limits>
#include "CountMinSketch.h"
#include "HashFunctions.h"

/**
 * @brief Increment the count of string s
 * 
 * @param s string needs to be counted
 */
void CountMinSketch::increment(const string & s) {
    // using for loop to using first K hash functions
    // for hashed indexs
    for(unsigned int i = 0; i < K; i++){
        unsigned int index = hash_functions[i](s);
        // hashed index should not be out of boundary M
        // if index is out of range, mod it by M to resize it
        if(index >= M){
            index %= M; 
        }
        // update count
        count[i][index] += 1;
    }
}

/**
 * @brief estimate the count of string s, i.e. 
 *        the estimation >= real count  
 * 
 * @param s string to be estimated
 * @return est an unsigned int which is the estimated count of 
 *         string s, or the maximun of <unsigned int> if any 
 *         hashed index of string s is out of boundary M
 */
unsigned int CountMinSketch::estimate(const string & s) {
    unsigned int est = numeric_limits <unsigned int>::max();
    for(unsigned int i = 0; i < K; i++){
        unsigned int index = hash_functions[i](s);
        // hashed index should not be out of boundary M
        // if index is out of range, mod it by M to resize it
        if(index >= M){
            index %= M;
        }

        unsigned int curr = count[i][index];
        if(curr < est){
            est = curr;
        }
    }
    return est;
}