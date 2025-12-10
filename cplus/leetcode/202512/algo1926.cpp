#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int m = maze.size(), n = maze[0].size();
        vector vis(m, vector<bool>(n, false));
        int ans = 0;
        vector<pair<int, int>> q;
        q.emplace_back(entrance[0], entrance[1]);
        vis[entrance[0]][entrance[1]] = true;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                if (ans && (x == 0 || x == m-1 || y == 0 || y == n-1 )) return ans;

                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && !vis[dx][dy] && maze[dx][dy]=='.'){
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