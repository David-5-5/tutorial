#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    int largestArea(vector<string>& grid) {
        // 自行解答，dfs 求每个连通块个数
        int m = grid.size(), n = grid[0].length();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y, int val) -> int {
            if (x <0 || x >=m || y<0 || y >= n || grid[x][y] == '0') return -2500;
            if (vis[x][y] || grid[x][y] != val) return 0;
            vis[x][y] = true;
            int res = 1;
            res += dfs(x+1, y, val); res += dfs(x-1, y, val); 
            res += dfs(x, y-1, val); res += dfs(x, y+1, val);
            return res;
        };

        int ans = 0;
        for (int i=1; i<m-1; ++i) for (int j=1; j<n-1; ++j) {
            if (vis[i][j] || grid[i][j] == '0') continue;
            int values = dfs(i, j, grid[i][j]);

            ans = max(ans, values);
        }
        return ans;
    }
};