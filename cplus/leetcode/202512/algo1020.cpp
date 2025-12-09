#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        // 自行解答
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> int {
            if (x <0 || x >=m || y<0 || y >= n) return -250000;
            if (grid[x][y] == 0 || vis[x][y]) return 0;
            vis[x][y] = true;
            
            int res = 1;
            res += dfs(x+1, y); res += dfs(x-1, y); res += dfs(x, y-1); res += dfs(x, y+1);
            return res;
        };

        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j] || grid[i][j] == 0) continue;
            int values = dfs(i, j);

            ans += max(0, values);
        }

        return ans;
    }
};