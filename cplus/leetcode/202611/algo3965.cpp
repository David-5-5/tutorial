#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime) {
        
        vector<vector<int>> g(n);
        for (auto & e: edges) {
            auto u = e[0], v = e[1];
            g[u].emplace_back(v); g[v].emplace_back(u); 
        }

        auto dfs = [&](this auto&& dfs, int u, int fa) -> long long {
            long long latest = LLONG_MIN, earliest = LLONG_MAX;
            for (auto & v : g[u]) {
                if (v == fa) continue;
                auto v_time = dfs(v, u);
                latest = max(v_time, latest); earliest = min(v_time, earliest);
            }

            if (latest == LLONG_MIN) return baseTime[u];
            else return baseTime[u] + 2 * latest - earliest;
        };

        return dfs(0, -1);
    }
};