#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  其他区间 DP
class Solution {
public:
    int getMoneyAmount(int n) {
        // 状态转移方程 dp(i, j) = min_{k=i}^j (k + max(dp(1,k-1), dp(k+1, j))
        // i == j dp(i, j) = 0

        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for (int i=n-1; i>=1; i--) {
            for (int j=i+1; j<=n; j++) {
                dp[i][j] = j + dp[i][j-1];
                for (int k=i; k<j; k++) {
                    dp[i][j] = min(dp[i][j], k + max(dp[i][k-1], dp[k+1][j]));
                }
            }
        }
        return dp[1][n];
    }
};