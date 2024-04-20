#include "Set.h"
/**
 * For map, it is important to not use [] operator to find element,
 * use find() instead, since using [] operator will create a default 
 * constructed element once meet an element not exist in the map. This
 * will cause severe error!!! Should always remember that.
 */
/**
 * Class constructor: initialize root node 
 * to new node, set the number of element to 0
 */
MultiwayTrieSet::MultiwayTrieSet() {
    root = new Node();
    numElements = 0;
}

/**
* Class destructor: delete all the children nodes,
* set root node to nullptr, and number of element to 0
*/
MultiwayTrieSet::~MultiwayTrieSet() {
    if(root == nullptr){
        // if tree is empty return back
        return;
    }else{
        // using <vector> class to hold every node 
        // in the trie
        vector<Node*> nodes;
        nodes.push_back(root);
        while(!nodes.empty()){
            // vector nodes keeps popping the last
            // element in the vector and store its children
            // until go through every node in the trie
            Node* curr = nodes.back();
            nodes.pop_back();
            if(!curr->children.empty()){
                for(pair<char, Node *> element : curr->children){
                    nodes.push_back(element.second);
                    // store all children of current node if they are not NULL
                }
                curr->children.clear(); 
                // clear all element in the children map 
                delete curr;
                numElements--;
            }else{
                // if the map is empty, simply delete the current node
                delete curr;
                numElements--;
            } 
        }
    }
    root = nullptr;
}

/**
 * Return the number of elements in the trie
 * @return numElements: the number of elements in
 * the trie  
 */
unsigned int MultiwayTrieSet::size() {
    return numElements;
}

/**
 * Insert a string into the trie, and update the
 * number of elements in the trie
 * @papram s: input string needs to be inserted 
 */
void MultiwayTrieSet::insert(string s) {
    Node* curr = root;
    for(char const &c : s){
        if(curr->children.find(c) == curr->children.end()){
            curr->children[c] = new Node();
            // create an new node if the char is not
            // existed in the trie
        }
        curr = curr->children[c];
    }
    // determine if the string exists in the trie by checking
    // the isWord boolean param in the last char node
    if(!curr->isWord){
        curr->isWord = true;
        numElements++;
        // turn the boolean isWord paramater to true
        // for a valid insertion  
    }
}

/**
 * Remove a string from the trie, and update the
 * number of elements in the trie
 * @papram s: input string needs to be removed  
 */
void MultiwayTrieSet::erase(const string & s) {
    Node* curr = root;
    for(char const &c : s){
        if(curr->children.find(c) == curr->children.end()){
            return;
            // end if the char is not exists in the trie
        }else{
            curr = curr->children[c];
        }
    }
    // determine if the string is in the trie by checking
    // the isWord param of the last char Node 
    if(curr->isWord){
        curr->isWord = false;
        // turn the param to false for a valid removal
        numElements--;
        // update number of emelent
    }
}

/**
 * Determine a string exists in the trie or not
 * @papram s: string needs to be checked in the set  
 * @return true if string in the array; otherwise, false
 */
bool MultiwayTrieSet::contains(const string & s) {
    Node* curr = root;
    for(char const &c : s){
        // simply check if every char in the trie
        if(curr->children.find(c) == curr->children.end()){
            return false;
        }else{
            curr = curr->children[c];
        }
    }
    // determine if the string exists in the trie by finally
    // checking the isWord param
    if(curr->isWord){
        return true;
        // return true for a valid word node
    }
    return false;
    // return false if no valid word node
}

