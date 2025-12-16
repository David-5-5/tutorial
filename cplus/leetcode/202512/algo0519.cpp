#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 随机算法 - 6.1 随机数
class Solution {
private:
    int m, n, tot;
    unordered_map<int, int> used;   // 最后的应该是使用过的
public:
    Solution(int m, int n) {
        this->m = m, this->n = n;
        tot = m * n;
    }
    
    vector<int> flip() {
        int inx = rand() % tot;
        vector<int> ans;
        if (used.count(inx)) {
            ans = {used[inx]/n, used[inx]%n};
        } else {
            ans = {inx/n, inx%n};
        }
        tot--;
        used[inx] = used.count(tot) ? used[tot] : tot;
        return ans;
    }
    
    void reset() {
        tot = m * n;
        used.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */