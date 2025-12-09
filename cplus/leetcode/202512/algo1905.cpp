#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        // 自行解答
        int m = grid2.size(), n = grid2[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> bool {
            if (x <0 || x >=m || y<0 || y >= n || grid2[x][y] ==0 || vis[x][y]) return true;
            vis[x][y] = true;
            bool cur = (grid1[x][y] == 1);
            bool up = dfs(x+1, y), down = dfs(x-1, y), left = dfs(x, y-1), right = dfs(x, y+1);
            return  cur && up && down && left && right;
        };

        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j] || grid2[i][j] == 0) continue;
            ans += dfs(i, j);
        }

        return ans;     
    }
};