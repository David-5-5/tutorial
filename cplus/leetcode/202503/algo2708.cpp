#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    long long maxStrength(vector<int>& nums) {
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