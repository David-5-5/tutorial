#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  子矩形 DP
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ans = 0;
        vector<vector<int>> dp(n, vector<int>(m, 0));
        for (int i = 0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j== 0) dp[i][j] = 1;
                    else dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                }
                ans = max(ans, dp[i][j]);
            }

        }
        return ans * ans;
    }
};