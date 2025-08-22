#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        // 自行解答
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }

        int ans = 0;
        auto dfs = [&] (this auto&& dfs, int u, int fa) -> long {
            long mx = 0; int mx_cnt = 0;

            for (auto & v:g[u]) {
                if (v == fa) continue;
                auto child = dfs(v, u);
                if (child > mx) {
                    mx_cnt = 1; mx = child;
                } else if (child == mx) mx_cnt ++;
            }
            ans += g[u].size() - (fa==-1?0:1) - mx_cnt;
            return mx + cost[u];
        };

        dfs(0, -1); return ans;    
    }
};