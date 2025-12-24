#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 网格图 DP - 2.1 基础
class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        // 递归 (python) 修改为递推 
        int m = grid.size(), n = grid[0].size();

        vector dp(m+1, vector(n+1, vector<int>(k+2, INT_MIN)));
        ranges::fill(dp[0][1].begin() + 1, dp[0][1].end(), 0);    // 初始化

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) for (int K=0; K<=k; ++K){
            int new_K = K - ( grid[i][j]> 0);
            dp[i+1][j+1][K+1] = grid[i][j] + max(dp[i][j+1][new_K+1], dp[i+1][j][new_K+1]);
        }

        int ans = dp[m][n][k+1];
        return ans >= 0? ans: -1;
    }
};