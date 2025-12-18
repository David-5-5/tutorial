#include <bits/stdc++.h>
using namespace std;

// 三、网格图 0-1 BFS
class Solution {
public:
    int minMoves(vector<string>& matrix) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<int> doors(26);
        vector door_coor(26, vector<pair<int, int>>());

        int m = matrix.size(), n = matrix[0].length();
        if (matrix[m-1][n-1] == '#') return -1;

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            auto& ch = matrix[i][j];
            if (ch >='A' && ch <= 'Z') door_coor[matrix[i][j]-'A'].emplace_back(i, j);
        }

        vector<pair<int, int>> q; vector vis(m, vector<bool>(n));
        if (matrix[0][0] == '.') {q.emplace_back(0, 0); vis[0][0] = true;}
        else for (auto& [doorx, doory]: door_coor[matrix[0][0]-'A']) {
            q.emplace_back(doorx, doory);  vis[doorx][doory] = true;
        }
        int step = 0;

        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y] : q) {
                if (x == m-1 && y == n-1) return step;
                for (auto& d : dirs) {
                    auto dx = x + d[0], dy = y + d[1];
                    if (dx < 0 || dx >= m || dy < 0 || dy >= n || vis[dx][dy] || matrix[dx][dy] == '#') continue;
                    if (matrix[dx][dy] == '.') {nxt.emplace_back(dx, dy); vis[dx][dy] = true;}
                    else for (auto& [doorx, doory]: door_coor[matrix[dx][dy]-'A']) {
                        nxt.emplace_back(doorx, doory);  vis[doorx][doory] = true;
                    }
                }
            }
            q = move(nxt); step ++;
        }
        return -1;      
    }

};