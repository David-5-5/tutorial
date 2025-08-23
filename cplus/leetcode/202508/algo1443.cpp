#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        // 自行解答
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        int ans = 0;
        auto dfs = [&] (this auto&& dfs, int u, int fa) -> bool {
            bool has = hasApple[u]; 
            for (auto v: g[u]) {
                if (v == fa) continue;
                auto child_has = dfs(v, u);
                if (child_has) {
                    ans += 2; has = true;
                }
            }
            return has;
        };
        dfs(0, -1); return ans;
    }
};