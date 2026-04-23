#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.4 换根 DP
class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        // 2026.4.15 复习 
        vector<int> ans(n); vector<vector<int>> g(n);
        for (auto e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> child_cnt(n);   // 
        auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
            child_cnt[u] += 1;  // 自身节点
            for (auto & v: g[u]) {
                if (v == fa) continue;
                dfs(v, u);
                ans[u] += ans[v] + child_cnt[v];
                child_cnt[u] += child_cnt[v];
            }
        };
        dfs(0, -1);
        auto dfs2 = [&](this auto&& dfs2, int u, int fa) -> void {
            // reroot
            ans[u] += (ans[fa]-ans[u]-child_cnt[u]) + (child_cnt[fa]-child_cnt[u]);
            child_cnt[u] = n;
            for (auto & v: g[u]) {
                if (v == fa) continue;
                dfs2(v, u);
            }
        };

        for (auto v: g[0]) dfs2(v, 0);
        return ans;
    }
};