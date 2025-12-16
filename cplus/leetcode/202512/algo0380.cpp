#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
class RandomizedSet {
private:
    vector<int> arr;
    unordered_map<int, int> v2i;
public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if (v2i.contains(val)) return false;
        v2i[val] = arr.size(); arr.emplace_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (!v2i.contains(val)) return false;
        int inx = v2i[val]; v2i.erase(val);
        if (inx != arr.size() - 1) {    // 最后元素移到 inx
            arr[inx] = arr.back();
            v2i[arr[inx]] = inx;
        }
        arr.pop_back();                 // 删除最后元素
        return true;
    }
    
    int getRandom() {
        int i = rand() % arr.size();
        return arr[i];
    }
};


/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */