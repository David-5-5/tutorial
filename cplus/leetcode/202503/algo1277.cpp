#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  子矩形 DP
class Solution {
public:
    int countSquares(vector<vector<char>>& matrix) {
        // 参考题解，状态转移方程
        // dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;, matrix[i][j] = 1
        //            1, i == 0 or j == 0
        // dp[i][j] = 0 , matrix[i][j] = 0
        int n = matrix.size(), m = matrix[0].size();
        int ans = 0;
        vector<vector<int>> dp(n, vector<int>(m, 0));
        for (int i = 0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j== 0) dp[i][j] = 1;
                    else dp[i][j] =  min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                }
                ans += dp[i][j];
            }

        }
        return ans;
    }
};