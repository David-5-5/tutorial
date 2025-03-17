#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  子矩形 DP
class Solution {
public:
    int countPyramids(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        
        int ans = 0;
        vector<vector<int>> dp(n,vector<int>(m, -1));
        for (int i=n-1; i>=0; i--) {
            for (int j=0; j<m; j++) {       // 金字塔
                if (grid[i][j] == 0) continue;
                if (i+1 == n || j-1 < 0 || j+1 == m) 
                    dp[i][j] = 0;
                else dp[i][j] = min(dp[i+1][j-1], min(dp[i+1][j], dp[i+1][j+1])) + 1;
                ans += dp[i][j];
            }
        }

        for (int i=0; i<n; i++) {         // 倒金字塔
            for (int j=0; j<m; j++) {
                if (grid[i][j] == 0) continue;
                if (i == 0 || j-1 < 0 || j+1 == m) 
                    dp[i][j] = 0;
                else dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i-1][j+1])) + 1;
                ans += dp[i][j];
            }
        } 
        return ans;  

    }
};