#include "Set.h"

/**
 * Return the number of elements in the set via
 * in-built size() function of <unordered_set> class
 * @return ht.size(): size of the set.  
 */
unsigned int HashTableSet::size() {
    return ht.size();
}

/**
 * Insert a string into the set
 * @papram s: input string needs to be inserted 
 */
void HashTableSet::insert(string s) {
    if(contains(s)){
        return;
        // end if string exists in the set
    }
    ht.insert(s);
}

/**
 * Remove a string from the set
 * @papram s: input string needs to be removed  
 */
void HashTableSet::erase(const string & s) {
    if(!contains(s)){
        return;
        // end if string is not in the set
    }
    ht.erase(s);
}

/**
 * Determine a string exists in the set or not
 * @papram s: string needs to be checked in the set  
 * @return true if string in the array; otherwise, false
 */
bool HashTableSet::contains(const string & s) {
    // use in-built find() function in <unordered_set> class
    // to determine if the string exists in the set or not
    if(ht.find(s) != ht.end()){
        return true;
    }

    return false;
}

