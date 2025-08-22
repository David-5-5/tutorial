#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        // 自行解答，读题题，把要求都用上
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0]-1, v = edge[1]-1;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        int ans = 0;
        auto dfs = [&] (this auto&& dfs, int u, int d, int fa) -> double {
            int child = g[u].size() - (fa == -1?0:1);
            // if (d > t) return 0; // 剪枝, 不过对性能没有影响
            // 若 target 为叶子节点, 青蛙可以一直呆到 t 秒. 即 d<t&&child
            if (target-1 == u) return 1.0 * (d==t||(d<t&&child==0)?1:0); 
            double res = 0;
            for (auto v: g[u]) {
                if (v == fa) continue;
                res += 1.0/child * dfs(v, d+1, u);
            }
            return res;
        };
        return dfs(0, 0, -1);
    }
};