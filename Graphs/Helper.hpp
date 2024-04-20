
#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
using namespace std;

class DisjSet{
public:
    int size;
    DisjSet* parent;
    string label;

DisjSet(string label): label(label),size(0),parent(nullptr){};

DisjSet* find(DisjSet* target){
    DisjSet* curr = target;
    if(curr->parent!=nullptr){
        curr = find(target->parent);
    }

    return curr;
}

void Union(DisjSet* lhs, DisjSet* rhs){
    DisjSet* set_lhs = find(lhs);
    DisjSet* set_rhs = find(rhs);

    if(set_lhs->label.compare(set_rhs->label) == 0){
        return;
    }

    // group by size
    if(set_lhs->size > set_rhs->size){
        set_rhs->parent = set_lhs;
        set_lhs->size += set_rhs->size;
    }else{
        set_lhs->parent = set_rhs;
        set_rhs->size += set_lhs->size;
    }

}
};

#endif