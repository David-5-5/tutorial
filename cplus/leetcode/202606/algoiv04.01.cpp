#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool findWhetherExistsPath(int n, vector<vector<int>>& graph, int start, int target) {
        vector<vector<int>> g(n);
        for (auto e: graph) {
            g[e[0]].push_back(e[1]);
        }

        vector<int> visited(n);

        auto dfs = [&](this auto&& dfs, int u) -> bool {
            if (u == target) return true;
            for (auto v: g[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    if (dfs(v)) return true;
                }
            }
            return false;
        };

        return dfs(start);
    }
};