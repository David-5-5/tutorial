#include <bits/stdc++.h>
using namespace std;

// 二、网格图 BFS
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int m = isWater.size(), n = isWater[0].size();
        vector ans(m, vector<int>(n, 0));
        vector<pair<int, int>> q;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (isWater[i][j] == 1) q.emplace_back(i, j);
        }
        int height = 0;
        while (!q.empty()) {
            vector<pair<int, int>> nxt;
            for (auto& [x, y]: q) {
                ans[x][y] = height;
                for (auto d : dirs) {
                    int dx = x + d[0], dy = y + d[1];
                    if (dx>=0 && dx<m && dy>=0 && dy<n && isWater[dx][dy]==0){
                        isWater[dx][dy] = 1;
                        nxt.emplace_back(dx, dy);
                    }
                }
            }
            q = move(nxt); height ++;
        }
        return ans;
    }
};