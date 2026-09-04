#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        // 脑筋急转弯 答案为 0, 1, 2
        // 如果初始为包含多块陆地 返回 0
        // 如果遍历所有陆地，删除其中一块后，出现多块返回 1
        // 否则返回 2

        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int m = grid.size(), n = grid[0].size(), cnt = 0;

        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            if (grid[i][j] == 1) cnt ++;
        }
        if (cnt <= 1) return cnt;   // 特殊情况判断

        auto check = [&](pair<int, int> del) -> int {
            int x, y;
            for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
                if (grid[i][j] == 1 && i!=del.first && j != del.second) {
                    x = i, y = j; break;
                }
            }

            set<int> vis;
            auto dfs = [&](this auto&& dfs, int i, int j) -> void {
                for (auto d: dirs) {
                    auto x = i+d[0], y = j+d[1];
                    if (x == del.first && y == del.second) continue;
                    if (x>=0 && x<m && y>=0 && y<n && grid[x][y] && !vis.count(x*n+y)) {
                        vis.insert(x*n+y); dfs(x, y);
                    }
                }
            };
            vis.insert(x*n+y);
            dfs(x, y);
            return vis.size();
        };

        if (check({-1, -1}) < cnt) return 0;
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            if (grid[i][j] == 1 && check({i, j}) < cnt - 1) return 1;
        }

        return 2;
    }
};