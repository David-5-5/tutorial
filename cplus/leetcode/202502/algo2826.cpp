#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        // 引用 300 LIS 方案
        vector<int> dp;
        for (auto& x : nums) {
            auto it = ranges::upper_bound(dp, x);
            if (it != dp.end()) *it = x;        // c++ iterator usage
            else dp.push_back(x);
        }

        return nums.size() - dp.size();
    }


};