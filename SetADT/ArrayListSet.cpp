#include "Set.h"
#include <algorithm>
/**
 * Include <algorithm> to use functions upper_bound()
 * and binary_search()
 */

/**
 * Return the number of elements in the array list set
 * via in-built size() function of c++ <vector> class
 * @return arr.size(): size of the array list.  
 */
unsigned int ArrayListSet::size() {
    return arr.size();
}

/**
 * Insert a string in an sorted order
 * @papram s: string needs to be inserted.  
 */
void ArrayListSet::insert(string s) {
    if(contains(s)){
        return;
        // stop if the string is existed in the array list
    }
    arr.insert(upper_bound(arr.begin(), arr.end(), s),s);
    // insert the string in an sorted order
}

/**
 * Remove an input string 
 * @papram s: string needs to be removed.  
 */
void ArrayListSet::erase(const string & s) {
    if(!contains(s)){
        return;
        // stop if the string is not existed in the array list
    }
    arr.erase(find(arr.begin(), arr.end(), s));
}

/**
 * Determine a string exists in the array list or not
 * @papram s: string needs to be checked.  
 * @return true if string in the array; otherwise, false
 */
bool ArrayListSet::contains(const string & s) {
    if(binary_search(arr.begin(), arr.end(), s)) {
        return true;
        // using binary search method to look for the string
    }
    return false;
}

