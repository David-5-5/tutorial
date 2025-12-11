#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        // 自行解答
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> bool {
            if (x <0 || x >=m || y<0 || y >= n) return 0;
            if (grid[x][y] == 1 || vis[x][y]) return 1;
            vis[x][y] = true;
            // 使用 && 运算符会短路，导致递归不完整，例如 dfs(x+1, y) == false，不会执行后续的递归
            // 在使用 && || 会遇到递归短路的问题，一定要注意
            // return dfs(x+1, y) && dfs(x-1, y) && dfs(x, y-1) && dfs(x, y+1);
            return dfs(x+1, y) * dfs(x-1, y) * dfs(x, y-1) * dfs(x, y+1);
        };

        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j] || grid[i][j] == 1) continue;
            ans += dfs(i, j);
        }

        return ans;
    }

    int closedIsland(vector<vector<int>>& grid) {
        // 参考题解， 由外至内
        int m = grid.size(), n = grid[0].size();
        auto dfs = [&](this auto&& dfs, int x, int y) -> void {
            if (x <0 || x >=m || y<0 || y >= n || grid[x][y] == 1) return;

            grid[x][y] = 1;
            dfs(x+1, y); dfs(x-1, y); dfs(x, y-1); dfs(x, y+1);
        };

        for (int i=0; i<m; ++i) {dfs(i, 0); dfs(i, n-1);}   
        for (int j=1; j<n-1; ++j) {dfs(0, j); dfs(m-1, j);}

        int ans = 0;
        for (int i=1; i<m-1; ++i) for (int j=1; j<n-1; ++j) {
            if (grid[i][j] == 1) continue;
            dfs(i, j); ans += 1;
        }

        return ans;
    }    
};