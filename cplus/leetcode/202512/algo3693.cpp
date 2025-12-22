#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 爬楼梯
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // 自行解答
        vector<int> dp(n+1);
        for (int i=1; i<=n; ++i) {
            int mn = INT_MAX;
            if (i-1>=0) mn = min(mn, dp[i-1] + 1);
            if (i-2>=0) mn = min(mn, dp[i-2] + 4);
            if (i-3>=0) mn = min(mn, dp[i-3] + 9);
            dp[i] = mn + costs[i];
        }

        return dp[n];
    }
};