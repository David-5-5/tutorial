#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 五、划分型 DP 5.3 约束划分个数
class Solution {
public:
    int minXor(vector<int>& nums, int k) {
        // 参考题解 好久不做 DP，都忘了
        int n = nums.size();
        vector dp(k+1, vector<int>(n+1, INT_MAX));

        dp[0][0] = 0;
        for (int i=1; i<=k; ++i) for (int j=1; j<=n; ++j) {
            int s = 0;
            for (int l=j-1; l>=i-1; l--) {
                s ^= nums[l];
                dp[i][j] = min(dp[i][j], max(dp[i-1][l], s));
            }
        }

        return dp[k][n];
    }
};