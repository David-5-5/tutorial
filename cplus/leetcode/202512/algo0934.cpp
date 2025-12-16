#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int x, y, n = grid.size();
        
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) if (grid[i][j] == 1) {
            x = i, y = j; break;
        }
        vector<pair<int, int>> q;
        auto dfs = [&](this auto&& dfs, int x, int y) -> void {
            if (x <0 || x >=n || y<0 || y >= n || grid[x][y] != 1) return;
            grid[x][y] = 2; q.emplace_back(x, y);       // grid[x][y] == 2 is visited
            dfs(x+1, y); dfs(x-1, y); dfs(x, y-1); dfs(x, y+1);
        };
        dfs(x, y); // dfs, find first island

        int dis = 0;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<n && dy>=0 && dy<n && grid[dx][dy]!=2){
                        if (grid[dx][dy] == 1) return dis;
                        grid[dx][dy] = 2;               // grid[dx][dy] == 2 is visited
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            q = move(nxt); dis ++;
        }
        return dis;
    }
};