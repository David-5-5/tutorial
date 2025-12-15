#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        // 参考题解，利用bfs，将陆地加入队列，然后将离陆地水域逐步加入队列，
        // 因此最后加入的水域就是举例最大的
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));
        vector<pair<int, int>> q;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (grid[i][j] == 1) q.emplace_back(i, j);
        }
        int ans = 0;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && !vis[dx][dy] && grid[dx][dy]==0){
                        vis[dx][dy] = true;
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            q = move(nxt); if (q.size()) ans ++;
        }
        return ans?ans:-1;
    }
};