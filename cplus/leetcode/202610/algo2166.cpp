#include <bits/stdc++.h>
using namespace std;

class Bitset {
private:
    int size;
    unordered_set<int> ones;
    int is_flip = 0;
public:
    Bitset(int size) : size(size) {
        
    }
    
    void fix(int idx) {
        if (is_flip) ones.erase(idx);
        else ones.insert(idx);
    }
    
    void unfix(int idx) {
        if (is_flip) ones.insert(idx);
        else ones.erase(idx);
    }
    
    void flip() {
        is_flip ^= 1;
    }
    
    bool all() {
        if (is_flip) return ones.empty();
        else return ones.size() == size;
    }
    
    bool one() {
        if (is_flip) return size - ones.size();
        else return ones.size();        
    }
    
    int count() {
        if (is_flip) return size - ones.size();
        else return ones.size();
    }
    
    string toString() {
        string ans(size, '0' + is_flip);
        for (auto & idx: ones) ans[idx] = is_flip?'0':'1';
        return ans;
    }
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */