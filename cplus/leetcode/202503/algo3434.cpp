#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 进阶
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;
        for (auto& target:st) {
            int f0 = 0, f1 = 0, f2 = 0;
            for (auto& x : nums)  {
                f2 = max(f2, f1) + (x==k);
                f1 = max(f1, f0) + (x == target);
                f0 += (x == k);
            }
            ans = max({ans, f1, f2});
        }

        return ans;

    }
};