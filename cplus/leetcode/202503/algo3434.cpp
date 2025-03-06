#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 进阶
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        // 参考题解 状态 dp
        int n = nums.size();

        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;
        for (auto& target:st) {
            int f0 = 0, f1 = 0, f2 = 0;
            for (auto& x : nums)  {                 // 状态转移方程
                f2 = max(f2, f1) + (x==k);          // 在子数组右，左+中+右
                f1 = max(f1, f0) + (x == target);   // 在子数组中，左+中
                f0 += (x == k);                     // 在子数组左，左
            }
            ans = max({ans, f1, f2});
        }

        return ans;

    }
};