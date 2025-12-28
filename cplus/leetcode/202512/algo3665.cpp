#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 网格图 DP - 2.2 进阶
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        // translate from python by doubao
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        // 三维DP数组：dp[i][j][k]
        // i,j：当前坐标；k：上一步方向（0=向下走的标记，1=向右走的标记）
        // 含义：从(i,j)出发，以上一步方向k走到终点的路径数
        vector<vector<vector<long long>>> dp(m, vector<vector<long long>>(n, vector<long long>(2, 0)));

        // 边界条件：终点(m-1,n-1)，无论方向是0/1，都只有1条路径（已到达终点）
        dp[m-1][n-1][0] = 1;
        dp[m-1][n-1][1] = 1;

        // 逆序递推：从右下角往左上角算（依赖i+1/j+1的结果）
        // 先遍历行（从倒数第二行到第0行）
        for (int i = m-1; i >= 0; --i) {
            // 遍历列（从倒数第二列到第0列）
            for (int j = n-1; j >= 0; --j) {
                // 跳过终点（已初始化）
                if (i == m-1 && j == n-1) continue;

                // 情况1：grid[i][j] = 0 → 可自由选择向下/向右
                if (grid[i][j] == 0) {
                    // 向下走的路径数：i+1未越界则取dp[i+1][j][0]，否则0
                    long long down = (i + 1 < m) ? dp[i+1][j][0] : 0;
                    // 向右走的路径数：j+1未越界则取dp[i][j+1][1]，否则0
                    long long right = (j + 1 < n) ? dp[i][j+1][1] : 0;
                    dp[i][j][0] = (down + right) % MOD;
                    dp[i][j][1] = (down + right) % MOD; // 方向0/1结果相同
                } else if (grid[i][j] == 1) { // 情况2：grid[i][j] = 1 → 限制方向
                    // 方向0：只能向右走
                    dp[i][j][0] = (j + 1 < n) ? dp[i][j+1][1] : 0;
                    dp[i][j][0] %= MOD;
                    // 方向1：只能向下走
                    dp[i][j][1] = (i + 1 < m) ? dp[i+1][j][0] : 0;
                    dp[i][j][1] %= MOD;
                }
            }
        }

        return (dp[1][0][0] + dp[0][1][1] ) % MOD; 
         
    }
};