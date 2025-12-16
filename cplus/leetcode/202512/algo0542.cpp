#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int m = mat.size(), n = mat[0].size();
        vector vis(m, vector<bool>(n, false));
        vector<pair<int, int>> q;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (mat[i][j] == 0) q.emplace_back(i, j);
        }
        int dis = 1;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && !vis[dx][dy] && mat[dx][dy]!=0){
                        vis[dx][dy] = true;
                        mat[dx][dy] = dis;
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            q = move(nxt); dis ++;
        }
        return mat;
    }
};