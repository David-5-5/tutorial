#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.1 遍历
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        // 自行解答
        vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());

        for (int i=0; i<n-1; ++i) {
            auto e = connections[i];
            auto & u = e[0], v = e[1];
            g[u].emplace_back(v, i); g[v].emplace_back(u, i);
        }
        int ans = 0;
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            for (auto& [v, i]: g[u] ) {
                if (v == fa) continue;
                if (connections[i][1] == v) ans ++;
                dfs(v, u);
            }
        };
        dfs(0, -1); return ans;       
    }
};