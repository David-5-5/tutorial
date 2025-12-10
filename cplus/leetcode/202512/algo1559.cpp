#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y, int prev_x, int prev_y) -> int {

            if (vis[x][y]) return true;
            vis[x][y] = true;

            if (x+1<m && x+1!=prev_x && grid[x][y] == grid[x+1][y] && dfs(x+1, y, x, y)) return true;
            if (x-1>=0 && x-1!=prev_x && grid[x][y] == grid[x-1][y] && dfs(x-1, y, x, y)) return true;
            if (y-1>=0 && y-1!=prev_y && grid[x][y] == grid[x][y-1] && dfs(x, y-1, x, y)) return true;
            if (y+1<n && y+1!=prev_y && grid[x][y] == grid[x][y+1] && dfs(x, y+1, x, y)) return true;
            return false;
        };

        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j]) continue;
            if (dfs(i, j, -1, -1)) return true;
        }

        return false;
    }
};