#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        // 自行解答，dfs 求每个连通块的权重和
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> int {
            if (x <0 || x >=m || y<0 || y >= n || vis[x][y] || grid[x][y] == 0) return 0;
            vis[x][y] = true;
            int res = grid[x][y];
            res += dfs(x+1, y); res += dfs(x-1, y);
            res += dfs(x, y-1); res += dfs(x, y+1);
            return res % k;
        };

        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j] || grid[i][j] == 0) continue;
            int values = dfs(i, j);

            ans += values%k==0?1:0;
        }

        return ans;
    }
};