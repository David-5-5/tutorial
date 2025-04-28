#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {

        int mx = 0, n = grid.size(), m = grid[0].size();
        for (auto& row:grid) for (auto& v:row) mx = max(mx, v);
        
        vector<vector<int>> f(mx+1, vector<int>(1<<n));

        vector<vector<int>> memo(mx+1, vector<int>(1 << n, -1));
        auto dfs = [&] (this auto&& dfs, int i, int s)->int {
            if (i == 0 || s == (1<<n) - 1) return 0;

            auto& res = memo[i][s];
            if (res != -1) return res;
            res = dfs(i-1, s);      // 不选
            for (int r=0; r<n; ++r) {
                if (s>>r & 1) continue;     // r 行已经选择
                for (int c = 0; c<m; ++c) {
                    if (grid[r][c] == i) res = max(res, i+dfs(i-1, s|1<<r));
                }
            }
            return res;
        };        
        
        return dfs(mx, 0);
    }
};