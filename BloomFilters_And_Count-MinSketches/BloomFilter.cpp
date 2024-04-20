/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: Stepik CH 5.9
 *
 * This file includes "insert" and "" function for a bloom filter.
 */

#include "BloomFilter.h"
#include "HashFunctions.h"

/**
 * @brief Insert string into this Bloom filter
 * 
 * @param s string to be inserted
 */
void BloomFilter::insert(const string & s) {
    // for loop to calculate the hashed indexs of this string
    // by using from 1st to Kth hash function 
    for (unsigned int i = 0; i < K;i++){
        unsigned int index = hash_functions[i](s);
        // hashed index should not be out of boundary M
        // if index is out of range, mod it by M to resize it
        if(index >= M){
            index %= M;  
        }
        bits[index] = true;
    }
}

/**
 * @brief Check if the string exists in the Bloom filter
 * 
 * @param s string to be checked
 * @return true if all elements with hased indexs (calculated by hash   
 *         functions no. 1 to K) are all true in the bits vector
 * @return false if: 1) any element with hashed index is false in 
 *                      the bit vector
 *                   2) if any hashed index of this string is out of
 *                      boundary of bit vector (index(s) >= M)
 */
bool BloomFilter::contains(const string & s) {
    for (unsigned int i = 0; i < K; i++){
        unsigned int index = hash_functions[i](s);
        if(index >= M){
            index %= M;
        }
        if(!bits[index]){
            return false;
        }
    }
    return true;
}