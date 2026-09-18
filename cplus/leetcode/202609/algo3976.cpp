#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        auto calc = [&](bool ismul) -> long long {
            // dp[i+1][0] 表示有端点为 i 的最大子数组和，且不修改任何元素
            // dp[i+1][1] 表示有端点为 i 的最大子数组和，且修改了 nums[i]
            // dp[i+1][2] 表示有端点为 i 的最大子数组和，在 nums[i] 左边区间发生修改
            vector dp(n+1, vector<long long>(3));
            long long res = LONG_MIN;
            for (int i=0; i<n; i++) {
                auto & x = nums[i]; long long y = ismul? 1LL * x * k : x / k;
                dp[i+1][0] = max(dp[i][0], 0LL) + x;
                dp[i+1][1] = max(dp[i][0], max(dp[i][1], 0LL)) + y;
                dp[i+1][2] = max(dp[i][1], max(dp[i][2], 0LL)) + x;

                res = max(res, max(dp[i+1][1], dp[i+1][2]));
            }
            return res;

        };

        return max(calc(true), calc(false));
    }
};