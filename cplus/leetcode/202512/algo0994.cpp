#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));
        vector<pair<int, int>> q;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (grid[i][j] == 2) q.emplace_back(i, j);
        }
        int ans = 0;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && !vis[dx][dy] && grid[dx][dy]==1){
                        vis[dx][dy] = true;
                        grid[dx][dy] = 2;
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            q = move(nxt); if (q.size()) ans ++;
        }

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (grid[i][j] == 1) return -1;
        }

        return ans;
    }
};