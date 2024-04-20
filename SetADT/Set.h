/*
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 *
 * Sources Used: I followed the pseudocode provided on Ch 6. on Stepik.
 *
 * This file is a tester file for CSE 100 in Spring 2022.
 * It provides definitions of the Sets that students are going to implement.
 */


#ifndef SET_H
#define SET_H

#include <list>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Abstract class to represent the Set ADT
 */
class Set {
public:
    /**
     * Return the number of elements in this Set
     *
     * @return number of elements inside the set
     */
    virtual unsigned int size() = 0;

    /**
     * Insert s into this Set. If the element is already in this Set, do not
     * make any changes to this Set.
     *
     * @param s string to be inserted into the set
     */
    virtual void insert(string s) = 0;

    /**
     * Remove s from this Set. If the element does not exist in this Set, do
     * not make any changes to this Set.
     *
     * @param s string to be removed from the set
     */
    virtual void erase(const string &s) = 0;

    /**
     * Check to see if a string exists in the set or not.
     *
     * @param s string to look for in the set
     * @return true if s exists in this Set, otherwise false
     */
    virtual bool contains(const string &s) = 0;
};

/**
 * Class to implement the Set ADT using an Array List (C++ vector class)
 */
class ArrayListSet : public Set {
protected:
    /**
     * C++ vector (which is an Array List) to use behind-the-scenes
     */
    vector<string> arr;

public:
    unsigned int size();

    void insert(string s);

    void erase(const string &s);

    bool contains(const string &s);
};

/**
 * Class to implement the Set ADT using a Hash Table (C++ unordered_set class)
 */
class HashTableSet : public Set {
protected:
    /**
     * C++ unordered_set (which is a Hash Table) to use behind-the-scenes
     */
    unordered_set<string> ht;

public:
    unsigned int size();

    void insert(string s);

    void erase(const string &s);

    bool contains(const string &s);
};

/**
 * Class to implement the Set ADT using a Linked List (C++ list class)
 */
class LinkedListSet : public Set {
protected:
    /**
     * C++ list (which is a Linked List) to use behind-the-scenes
     */
    list<string> linked;

public:
    unsigned int size();

    void insert(string s);

    void erase(const string &s);

    bool contains(const string &s);
};

/**
 * Class to implement the Set ADT using a Red-Black Tree (C++ set class)
 */
class RedBlackTreeSet : public Set {
protected:
    /**
     * C++ set (which is a Red-Black Tree) to use behind-the-scenes
     */
    set<string> rbt;

public:
    unsigned int size();

    void insert(string s);

    void erase(const string &s);

    bool contains(const string &s);
};

/**
 * Class to implement the Set ADT using a Multiway Trie
 */
class MultiwayTrieSet : public Set {
public:
    /**
     * Nested helper Node class
     */
    class Node {
    public:
        /**
         * Boolean to keep track of if this is a "word" node
         */
        bool isWord;

        /**
         * Child pointers, where keys are letters and values are Node*
         */
        unordered_map<char, Node *> children;

        /**
         * Node constructor, which initializes everything
         */
        Node() : isWord(false) {}
    };

    /**
     * MultiwayTrieSet Constructor, which should initialize an empty MWT
     */
    MultiwayTrieSet();

    /**
     * MultiwayTrieSet Destructor, which should deallocate anything dynamic
     */
    ~MultiwayTrieSet();

    unsigned int size();

    void insert(string s);

    void erase(const string &s);

    bool contains(const string &s);

protected:
    /**
     * Pointer to the root node of this MWT
     */
    Node *root;

    /**
     * Total number of elements currently in the MWT
     */
    unsigned int numElements;
};

#endif
