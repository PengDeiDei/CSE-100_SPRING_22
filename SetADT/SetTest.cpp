/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: I followed the pseudocode provided on Ch 6. on Stepik.
 *
 * This file is a tester file for CSE 100 in Spring 2022.
 * It provides a sanity test for the multiway trie set.
 * This file is not graded. We highly encourage you to add your own test cases
 * here.
 */


#include "Set.h"
using namespace std;

/* Macro to explicity print tests that are run along with colorized result. */
#define TEST(EX) (void)((fprintf(stdout, "(%s:%d) %s:", __FILE__, __LINE__,\
                 #EX)) && ((EX && fprintf(stdout, "\t\x1b[32mPASSED\x1b[0m\n"))\
                 || (fprintf(stdout, "\t\x1b[31mFAILED\x1b[0m\n")) ))

/**
 * Sanity test on the multiway trie.
 */
void testSanity() {
    MultiwayTrieSet mt;
    mt.insert("test");
    TEST(mt.contains("test") == true);
    TEST(mt.size() == 1);
    mt.erase("test");
    TEST(mt.size() == 0);
}

/**
 * Sanity test on the array list.
 */
void testSanity_arr() {
    ArrayListSet arr;
    arr.insert("test");
    arr.insert("another");
    TEST(arr.contains("test") == true);
    TEST(arr.size() == 2);
    arr.erase("another");
    TEST(arr.size() == 1);
}

/**
 * Sanity test on the linked list.
 */
void testSanity_linked() {
    LinkedListSet linked;
    linked.insert("test");
    linked.insert("another");
    TEST(linked.contains("test") == true);
    TEST(linked.size() == 2);
    linked.erase("test");
    TEST(linked.size() == 1);
}

/**
 * Sanity test on the hash table.
 */
void testSanity_ht() {
    HashTableSet ht;
    ht.insert("test");
    ht.insert("another");
    TEST(ht.contains("test") == true);
    TEST(ht.size() == 2);
    ht.erase("test");
    TEST(ht.size() == 1);
}

/**
 * Sanity test on the red-black tree.
 */
void testSanity_rbt() {
    RedBlackTreeSet rbt;
    rbt.insert("test");
    rbt.insert("");
    rbt.insert("another");
    TEST(rbt.contains("") == true);
    TEST(rbt.size() == 3);
    rbt.erase("test");
    TEST(rbt.size() == 2);
}

const vector<string> ALL_WORDS =  {"apple", "grape", "RANDOM", "word", "vector", " ", "~^&()-+=/", "t", "test", "te", "testing", "tester", "T", "Test", "TesTing",};
const vector<string> DUPLI_WORDS =  {"apple","apple","grape","grape","RANDOM","RANDOM"};

void testEmptyString() {
    MultiwayTrieSet mwt;

    TEST(mwt.contains("a") == false);
    TEST(mwt.contains("a") == false);
    TEST(mwt.size() == 0);
    mwt.erase("");
    mwt.erase("");
    TEST(mwt.contains("") == false);
    TEST(mwt.size() == 0);
}

void testInsert() {
    size_t count = 0;
    MultiwayTrieSet mwt;
    for(auto curr: ALL_WORDS){
        mwt.erase(curr);
        mwt.erase(curr);
        mwt.erase(curr);
        TEST(mwt.contains(curr) == false);
        TEST(mwt.size() == count);

        mwt.insert(curr);
        TEST(mwt.contains(curr) == true);
        TEST(mwt.size() == ++count);

        mwt.erase(curr);
        TEST(mwt.contains(curr) == false);
        TEST(mwt.size() == --count);

        mwt.insert(curr); 
        TEST(mwt.contains(curr) == true);
        TEST(mwt.size() == ++count);

        mwt.insert(curr); 
        TEST(mwt.contains(curr) == true);
        TEST(mwt.size() == count);
    }


}

void testDuplicate(){
    size_t count = 0;
    MultiwayTrieSet mwt;
    for(auto curr: DUPLI_WORDS){
        mwt.erase(curr);
        TEST(mwt.contains(curr) == false);
        TEST(mwt.size() == count);

        mwt.insert(curr);
        TEST(mwt.contains(curr) == true);
        TEST(mwt.size() == ++count);

        mwt.erase(curr);
        TEST(mwt.contains(curr) == false);
        TEST(mwt.size() == --count);

        mwt.insert(curr); 
        TEST(mwt.contains(curr) == true);
        TEST(mwt.size() == ++count);

        mwt.insert(curr); 
        TEST(mwt.contains(curr) == true);
        TEST(mwt.size() == count);

        mwt.erase(curr);
        count--;
    }
}
/**
 * Test the Set implementations
 */
int main() {
    testEmptyString();
    //testInsert();
    //testDuplicate();
}
