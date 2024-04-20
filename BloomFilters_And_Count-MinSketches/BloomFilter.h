/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: Stepik CH 5.9
 *
 * This file provides the interface for a bloom filter.
 */

#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <string>
#include <vector>

using namespace std;

/**
 * Class to implement a Bloom Filter that stores strings
 */
class BloomFilter {
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
     * Bitset (boolean vector) of length m
     */
    vector<bool> bits;

public:
    /**
     * BloomFilter constructor
     *
     * @param k number of hash functions to use
     * @param m length of the bitset
     */
    BloomFilter(const unsigned int &k, const unsigned int &m) :
            K(k), M(m), bits(m, false) {}

    /**
     * Insert string s into this BloomFilter
     *
     * @param s string to insert
     */
    void insert(const string &s);

    /**
     * Return false if s definitely doesn't exist in this BloomFilter,
     * or true if s MIGHT exist in this BloomFilter
     *
     * @param s target string
     * @return whether the string doesn't exist or might exist in this filter
     */
    bool contains(const string &s);
};

#endif
