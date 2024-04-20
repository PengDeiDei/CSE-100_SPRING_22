#include "Set.h"
/**
 * Include <algorithm> to use functions find()
 */
#include <algorithm>

/**
 * Return the number of elements in the list
 * via in-built size() function of c++ <list> class
 * @return linked.size(): size of the array list.  
 */
unsigned int LinkedListSet::size() {
    return linked.size();
}

/**
 * Insert a string at the front of the list
 * and sort the list after insertion
 * @papram s: string needs to be inserted.  
 */
void LinkedListSet::insert(string s) {
    if(contains(s)){
        return;
        // end if the string exists in the list
    }
    linked.insert(linked.begin(),s);
    linked.sort();
}

/**
 * Remove an input string 
 * @papram s: string needs to be removed.  
 */
void LinkedListSet::erase(const string & s) {
    if(!contains(s)){
        return;
        // end if the string is not existed in the list
    }
    linked.remove(s);
}

/**
 * Determine a string exists in the list or not
 * @papram s: string needs to be checked.  
 * @return true if string in the array; otherwise, false
 */
bool LinkedListSet::contains(const string & s) {
    if(find(linked.begin(), linked.end(), s) != linked.end()){
        return true;
        // use find() function to determine if the
        // string exists in the list or not
    }
    return false;
}

