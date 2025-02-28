#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        // 参考题解，
        // 以下 ----- 关键代码 ---
        unordered_map<int, int> t;
        for (int i=0; i<target.size(); i++) t[target[i]] = i;

        vector<int> arr_t;
        for (auto& x: arr) 
            if (t.count(x)) arr_t.push_back(t[x]);        
        // 以上 ----- 关键代码 ---

        // 后续使用 300
        vector<int> dp;
        for (auto& x : arr_t) {
            auto it = ranges::lower_bound(dp, x);   // lower 严格递增
            if (it != dp.end()) *it = x;            // c++ iterator usage
            else dp.push_back(x);
        }

        return target.size() - dp.size();       
    }
};