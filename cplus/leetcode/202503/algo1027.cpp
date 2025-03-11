#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 合法子序列 DP
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        // 自行解答
        unordered_map<long, int> dp;
        int ans = 2;
        int mx = ranges::max(nums), mn = ranges::min(nums);

        for (auto& x: nums) {
            for (int d=(mn-mx)/2; d<=(mx-mn)/2; d++) {
                long mask = (long) d << 32 | x;
                long prev = (long) d << 32 | x - d;
                dp[mask] = dp[prev] + 1;
                ans = max(ans, dp[mask]);
            }
        }
        return ans;

    }
};