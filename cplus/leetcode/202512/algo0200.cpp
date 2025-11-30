#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        // 自行解答，dfs 求连通块的数量
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> void {
            if (x <0 || x >=m || y<0 || y >= n || vis[x][y] || grid[x][y] == '0') return;
            vis[x][y] = true;
            dfs(x+1, y); dfs(x-1, y); dfs(x, y-1); dfs(x, y+1);
        };

        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j] || grid[i][j] == '0') continue;
            ans += 1;  dfs(i, j);
        }

        return ans;
    }
};