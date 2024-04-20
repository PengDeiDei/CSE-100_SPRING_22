#include "Set.h"

/**
 * Return the number of elements in the set via
 * in-built size() function of c++ <set> class
 * @return rbt.size(): size of the set.  
 */
unsigned int RedBlackTreeSet::size() {
    return rbt.size();
}

/**
 * Insert a string into the set
 * @papram s: input string needs to be inserted 
 */
void RedBlackTreeSet::insert(string s) {
    if(contains(s)){
        return;
        // end if the string exists
    }
    rbt.insert(rbt.begin(),s);
}

/**
 * Remove a string from the set
 * @papram s: input string needs to be removed  
 */
void RedBlackTreeSet::erase(const string & s) {
    if(!contains(s)){
        return;
        // end if the string does not exist
    }
    rbt.erase(rbt.find(s));
}

/**
 * Determine a string exists in the set or not
 * @papram s: string needs to be checked in the set  
 * @return true if string in the array; otherwise, false
 */
bool RedBlackTreeSet::contains(const string & s) {
    if(rbt.find(s) != rbt.end()){
        return true;
    }

    return false;
}

