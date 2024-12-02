#include "DisjointSets.h"

DisjointSets::DisjointSets(int numElements) : s(numElements, -1){}

void DisjointSets::unionSets(int root1, int root2){
    if(s[root2] < s[root1]){
        s[root1] = root2;
    }else{
        if(s[root1] == s[root2]){
            --s[root1];
        }
        s[root2] = root1;
    }
}
int DisjointSets::find(int x) const{
    if(s[x] < 0){
        return x;
    }else{
        return find(s[x]);
    }
}

int DisjointSets::find(int x){
    if(s[x] < 0){
        return x;
    }else{
        return s[x] = find(s[x]);
    }
}