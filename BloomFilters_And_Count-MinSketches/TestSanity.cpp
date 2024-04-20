/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: None.
 *
 * This file provides some test cases for PA5.
 */

#include "BloomFilter.h"
#include "CountMinSketch.h"
using namespace std;

/* Macro to explicity print tests that are run along with colorized result. */
#define TEST(EX) (void)((fprintf(stdout, "(%s:%d) %s:", __FILE__, __LINE__,\
                 #EX)) && ((EX && fprintf(stdout, "\t\x1b[32mPASSED\x1b[0m\n"))\
                 || (fprintf(stdout, "\t\x1b[31mFAILED\x1b[0m\n")) ))

/**
 * Sanity test on the bloom filter.
 */
void testBloomFilter() {
    BloomFilter bf(5,10000000);
    bf.insert("mango");
    bf.insert("");
    bf.insert("mango");
    bf.insert("150");
    bf.insert("~^&=");
    bf.insert("~^&+-!");

    TEST(bf.contains("")==true);
    TEST(bf.contains("mango") == true);
    TEST(bf.contains("Test") == false);
    TEST(bf.contains("150") == true);
    TEST(bf.contains("~^&+-!") == true);
}

/**
 * Sanity test on the count min sketch.
 */
void testCountMinSketch() {
    CountMinSketch cms(5,10000000);
    cms.increment("apple");
    cms.increment("apple");
    
    TEST(cms.estimate("APPLE") == 0);
    cms.increment("APPLE");
    TEST(cms.estimate("~^&+-!") == 0);
    cms.increment("~^&+-!");
    TEST(cms.estimate("apple") >= 2);
    TEST(cms.estimate("test") == 0);
    TEST(cms.estimate("~^&+-!") > 0);
}

/**
 * Test the Set implementations
 */
int main() {
    //testBloomFilter();
    testCountMinSketch();
}