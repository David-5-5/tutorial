#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        
        const int mod = 1e9 + 7;
        vector<vector<vector<int>>> memo(maxMove, vector<vector<int>>(m, vector<int>(n, -1)));
        auto dfs = [&](this auto&& dfs, int i, int r, int c) {
            if (r <0 || r >= m || c < 0 || c >= n) return 1;
            if (i == maxMove) return 0;

            auto& res = memo[i][r][c];
            if (res != -1) return res;

            return res = ((long)dfs(i+1, r+1, c) + dfs(i+1, r-1, c) + dfs(i+1, r, c-1) + dfs(i+1, r, c+1)) % mod;        
        };

        return dfs(0, startRow, startColumn);  
    }
};