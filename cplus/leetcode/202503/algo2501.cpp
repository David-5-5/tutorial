#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 合法子序列 DP
class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<int, int> pos;
        vector<int> dp(n, 1);
        pos[nums[0]] = 0;

        int ans = 1;
        for (int i = 1; i < n; i++) {
            int x = (int) sqrt(nums[i]);
            if (x*x == nums[i] && pos.count(x)) {
                dp[i] = dp[pos[x]] + 1;
            }
            pos[nums[i]] = i;
            ans = max(ans, dp[i]);
        }
        return ans>1?ans:-1;   
    }
};  