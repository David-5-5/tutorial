#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        // 自行解答
        int m = grid.size(), n = grid[0].size();
        vector ans(m, vector<int>(n, -1));
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> void {
            if (x <0 || x >=m || y<0 || y >= n || grid[x][y] != grid[row][col] || vis[x][y]) return;
            vis[x][y] = true;
            
            if (x==0 || grid[x-1][y]!=grid[row][col] || x==m-1 || grid[x+1][y]!=grid[row][col] ||
                y==0 || grid[x][y-1]!=grid[row][col] || y==n-1 || grid[x][y+1]!=grid[row][col]) 
                ans[x][y] = color;
            dfs(x+1, y); dfs(x-1, y); dfs(x, y-1);dfs(x, y+1);
        };

        dfs(row, col);

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) 
            if (ans[i][j] == -1) ans[i][j] = grid[i][j];
        

        return ans;    
    }
};