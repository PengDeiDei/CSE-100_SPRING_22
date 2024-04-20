/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: Stepik CH 5.10.
 *
 * This file provides the interface for a count-min sketch.
 */

#ifndef COUNTMINSKETCH_H
#define COUNTMINSKETCH_H

#include <string>
#include <vector>

using namespace std;

/**
 * Class to implement a CountMinSketch that stores strings
 */
class CountMinSketch {
protected:
    /**
     * Number of hash functions to use (must be in range 1,5])
     */
    const unsigned int K;

    /**
     * Length of the bitset (m)
     */
    const unsigned int M;

    /**
     * Count matrix with k rows and m columns
     */
    vector <vector<unsigned int>> count;

public:
    /**
     * CountMinSketch constructor
     *
     * @param k number of hash functions to use
     * @param m length of the bitset
     */
    CountMinSketch(const unsigned int &k, const unsigned int &m) :
            K(k), M(m), count(K,vector<unsigned int>(M,0)) {}

    /**
     * Increment the count of s
     *
     * @param s string to increment count
     */
    void increment(const string &s);

    /**
     * Return an over-estimate of the count of string s
     *
     * @param s target string
     * @return over-estimate of the count of string s
     */
    unsigned int estimate(const string &s);
};

#endif
