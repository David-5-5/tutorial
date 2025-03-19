#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        // 自行解答
        const int mod = 1e9 + 7;
        vector<vector<vector<int>>> memo(maxMove, vector<vector<int>>(m, vector<int>(n, -1)));
        auto dfs = [&](this auto&& dfs, int i, int r, int c) {
            if (r <0 || r >= m || c < 0 || c >= n) return 1;    // 在矩形之外，满足条件
            if (i == maxMove) return 0;                         // 边界中止

            auto& res = memo[i][r][c];
            if (res != -1) return res;
            
            // 向上、下、左、右四个方向移动
            return res = ((long)dfs(i+1, r+1, c) + dfs(i+1, r-1, c) + dfs(i+1, r, c-1) + dfs(i+1, r, c+1)) % mod;        
        };

        return dfs(0, startRow, startColumn);  
    }
};