#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        // 自行解答 dfs + 位运算，还是挺有技巧
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));
        int left = 2 | 16 | 64, right = 2 | 8 | 32, up = 4 | 8 | 16, down = 4 | 32 | 64;
        auto dfs = [&](this auto&& dfs, int x, int y, int expect) -> bool {
            if (x <0 || x >=m || y<0 || y >= n || vis[x][y]) return false;
            int val = grid[x][y]; vis[x][y] = true;
            if (((expect >> val) & 1) == 0) return false;
            if (x == m-1 && y == n-1)  return true;
            
            switch (val) {
                case 1:
                    if (dfs(x, y-1, left) || dfs(x,y+1, right)) return true;
                    break;
                case 2:
                    if (dfs(x-1, y, up) || dfs(x+1,y, down)) return true;
                    break;
                case 3:
                    if (dfs(x, y-1, left) || dfs(x+1,y, down)) return true;
                    break;
                case 4:
                    if (dfs(x, y+1, right) || dfs(x+1,y,  down)) return true;
                    break;
                case 5:
                    if (dfs(x, y-1, left) || dfs(x-1,y, up)) return true;
                    break;
                case 6:
                    if (dfs(x, y+1, right) || dfs(x-1, y , up)) return true;
                    break;
            }
            return false;

        };
        return dfs(0, 0, (1<<8)-1); 
    }
};