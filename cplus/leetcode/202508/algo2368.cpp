#include <bits/stdc++.h>
using namespace std;

// 一般树
class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        // 自行解答
        vector<vector<int>> g(n, vector<int>());
        set<int> rest(restricted.begin(), restricted.end());

        for (auto & e : edges) {
            auto & u = e[0], v = e[1];
            g[u].push_back(v); g[v].push_back(u);
        }
        vector<bool> vis(n);
        int ans = 0;
        auto dfs = [&](this auto&& dfs, int u) -> void {
            ans ++;
            for (auto& v: g[u] ) {
                if (vis[v] || rest.count(v)) continue;
                vis[v] = true; dfs(v);
            }
        };
        vis[0]=true; dfs(0); return ans;       
    }

    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        // 自行解答
        vector<vector<int>> g(n, vector<int>());
        set<int> rest(restricted.begin(), restricted.end());

        for (auto & e : edges) {
            auto & u = e[0], v = e[1];
            g[u].push_back(v); g[v].push_back(u);
        }
        int ans = 0;
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            ans ++;
            for (auto& v: g[u] ) {
                if (v == fa || rest.count(v)) continue;
                dfs(v, u);
            }
        };
        dfs(0, -1); return ans;         
    }
};