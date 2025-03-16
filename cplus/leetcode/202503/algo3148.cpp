#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  子矩形 DP
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        // 自行解答
        int m = grid.size(), n = grid[0].size();

        // mx[i][j] 为 (i, j) 为左上角顶点 (m-1, n-1)为右下角 的矩阵的元素的最大值
        vector<vector<int>> mx(m, vector<int>(n));
        for (int r=m-1; r>=0; r--) {
            for (int c=n-1; c>=0; c--) {
                int prev = max((r+1<m)?mx[r+1][c]:0, (c+1<n)?mx[r][c+1]:0);
                mx[r][c] = max(grid[r][c], prev);
            }
        }

        int ans = INT_MIN/2;
        for (int r=0; r<m; r++) {
            for (int c=0; c<n; c++) {
                ans = max(ans, (r+1<m)?mx[r+1][c] - grid[r][c]:INT_MIN/2);
                ans = max(ans, (c+1<n)?mx[r][c+1] - grid[r][c]:INT_MIN/2);
            }
        }

        return ans;
    }
};