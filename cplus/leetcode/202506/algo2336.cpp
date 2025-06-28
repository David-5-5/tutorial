#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.1 堆 - 基础
class SmallestInfiniteSet {
private:
    set<int> sset;
public:
    // 数据量不大,直接用 set
    SmallestInfiniteSet() {
        for (int i=1; i<=1000; ++i) sset.emplace(i);
    }
    
    int popSmallest() {
        int val = *sset.begin();
        sset.erase(sset.begin());
        return val;
    }
    
    void addBack(int num) {
        sset.emplace(num);
    }
};


class SmallestInfiniteSet {
private:
    int thres = 1;      // thres 以下默认都在 set 中
    set<int> sset;
public:
    // 参考题解 - 很精妙
    SmallestInfiniteSet() {
    }
    
    int popSmallest() {
        if (sset.empty()) return thres++;
        
        int val = *sset.begin();
        sset.erase(sset.begin());
        return val;
    }
    
    void addBack(int num) {
        if (num < thres)
            sset.emplace(num);
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */