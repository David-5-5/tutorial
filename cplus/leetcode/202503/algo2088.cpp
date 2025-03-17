#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  子矩形 DP
class Solution {
public:
    int countPyramids(vector<vector<int>>& grid) {
        // 参考题解 
        // f[i][j] 为金子塔的顶端
        // f[i][j] = -1 grid[i][j] = 0
        // f[i][j] = 0  grid[i][j] = 1 f[i+1][j-1],f[i+1][j],f[i+1][j+1]有等于 -1 的情况
        // f[i][j] = x = min(f[i+1][j-1],f[i+1][j],f[i+1][j+1]) + 1 是 高度为 x+1 的金字塔，有 x 个
        // 因此 i 从 最后一行开始计算，
        // 倒金字塔从第一行开会计算，状态转移方程为：
        // f[i][j] = x = min(f[i-1][j-1],f[i-1][j],f[i-1][j+1]) + 1
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