#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        vector ans(n, vector<int>(m));
        vector<pair<int, int>> q;
        for (auto & src: sources) {
            auto & r = src[0], & c = src[1], & color = src[2];
            ans[r][c] = color; q.emplace_back(r, c);
        }

        while (!q.empty()) {
            unordered_map<int, int> colors;
            for (auto &[r, c] : q) {
                for (auto & d : dirs) {
                    auto x = r + d[0], y = c + d[1];
                    if (x>=0 && x < n && y>=0 && y < m && ans[x][y]==0) {
                        colors[x*m+y] = max(colors[x*m+y], ans[r][c]);
                    }
                }
            }
            vector<pair<int, int>> nxt;
            for (auto & [p, c]: colors) {
                auto x = p / m, y = p % m;
                ans[x][y] = c; nxt.emplace_back(x, y);
            }
            q = move(nxt);
        }

        return ans;
    }
};