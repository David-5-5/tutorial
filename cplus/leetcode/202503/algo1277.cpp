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

    int countSquares2(vector<vector<char>>& matrix) {
        // 2025.04 前缀和 时间复杂度 O(min(m,n)nm)
        int m = matrix.size(), n = matrix[0].size();

        vector<vector<int>> pres(m+1, vector<int>(n+1));
        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            pres[i+1][j+1] = matrix[i][j] + pres[i][j+1] + pres[i+1][j] - pres[i][j];

            int k = 0;
            while (k<=i && k<=j && pres[i+1][j+1] + pres[i-k][j-k] - pres[i+1][j-k] - pres[i-k][j+1] == (k+1)*(k+1))
                k ++;
            ans += k;
        }
        return ans;
    }

};