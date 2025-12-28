#include <bits/stdc++.h>
using namespace std;

// 网格图 五、综合应用
class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        // 自行解答，暴力 BFS
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        // 由于 blocked 长度有限，检查是否在有限步仍继续搜索，即 !q.empty()
        int mx_step = blocked.size() * 2;

        auto check = [&] (vector<int>& source, vector<int>& target) -> bool {
            set<pair<int, int>> vis;
            for (auto b: blocked) vis.emplace(b[0], b[1]);
            vector<pair<int, int>> q; q.emplace_back(source[0], source[1]); vis.emplace(source[0], source[1]);
            for (int i=0; i<mx_step && !q.empty(); i++) {
                vector<pair<int, int>> nxt;
                for (auto& [x, y]: q) {
                    if (x == target[0] && y == target[1]) return true;
                    for (auto& [dx, dy] :dirs) {
                        auto nx = x + dx, ny = y + dy;
                        if (nx<0 || nx >= 1e6 || ny<0 || ny >= 1e6 ||vis.count({nx, ny})) continue;
                        nxt.emplace_back(nx, ny); vis.emplace(nx, ny);
                    }
                }
                q = move(nxt);
            }

            return !q.empty();
        };

        return check(source, target) && check(target, source);
    }
};