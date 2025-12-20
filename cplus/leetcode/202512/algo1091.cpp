#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        // 自行解答
        const int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        int m = grid.size(), n = grid[0].size();
        vector vis(m, vector<bool>(n, false));
        int ans = 1;
        vector<pair<int, int>> q;
        if (grid[0][0] == 1) return -1;
        q.emplace_back(0, 0);
        vis[0][0] = true;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                if (x == m-1 && y == n-1) return ans;

                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && !vis[dx][dy] && grid[dx][dy]==0){
                        vis[dx][dy] = true;
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            ans ++; q = move(nxt);
        }
        return -1;
    }
};