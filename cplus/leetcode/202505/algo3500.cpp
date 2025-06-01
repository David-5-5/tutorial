#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.7 斜率优化 DP
class Solution {
public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        // 参考题解 划分型DP + abel 求和
        int n = cost.size();
        vector<int> pre_cost(n+1);
        for(int i=1; i<=n; i++) pre_cost[i] = pre_cost[i-1] + cost[i-1];

        int sum_num = 0;
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        for (int i=1; i<=n; ++i) {
            sum_num += nums[i-1];
            for(int j=0; j<i; ++j) {
                dp[i] = min(dp[i], dp[j] + (long long)sum_num * (pre_cost[i]-pre_cost[j]) +
                              (long long) k*(pre_cost[n]-pre_cost[j]));
            }
        }

        return dp[n];
    }
};