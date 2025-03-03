#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    long long maxStrength(vector<int>& nums) {
        // 自行解答 动态规划
        int n = nums.size();
        long mx = nums[0], mn = nums[0];
        for (int i=1; i<n; i++) {
            long x = nums[i], tmp = mn;
            mn = min({x, x*mn, x*mx, mn});
            mx = max({x, x*tmp, x*mx, mx});
        }

        return mx;        
    }

    long long maxStrength2(vector<int>& nums) {
        // 参考题解，简化版本
        int n = nums.size();
        long mx = nums[0], mn = nums[0];
        for (int i=1; i<n; i++) {
            long x = nums[i], tmp = mn;
            mn = min({x, x*mn, x*mx, mn});
            mx = max({x, x*tmp, x*mx, mx});
        }

        return mx;        
    }
};