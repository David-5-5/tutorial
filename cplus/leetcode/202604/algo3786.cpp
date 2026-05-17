#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.5 贡献法
class Solution {
public:
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        // reroot based on 834 需要灵活运用
        vector<vector<int>> g(n);
        for (auto e : edges) {
            g[e[0]].push_back(e[1]); g[e[1]].push_back(e[0]);
        }
        
        auto calc = [&] (int grp) -> long long {
            long long res = 0;
            vector<long long> ans(n); 
            vector<long long> child_cnt(n);   // 
            auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
                if (group[u] == grp) child_cnt[u] += 1;  // 自身节点
                for (auto & v: g[u]) {
                    if (v == fa) continue;
                    dfs(v, u);
                    ans[u] += ans[v] + child_cnt[v];
                    child_cnt[u] += child_cnt[v];
                }
            };
            dfs(0, -1);
            if (group[0] == grp) res += ans[0];
            auto dfs2 = [&](this auto&& dfs2, int u, int fa) -> void {
                // reroot
                ans[u] += (ans[fa]-ans[u]-child_cnt[u]) + (child_cnt[fa]-child_cnt[u]);
                child_cnt[u] = child_cnt[fa];
                if (group[u] == grp) res += ans[u];
                for (auto & v: g[u]) {
                    if (v == fa) continue;
                    dfs2(v, u);
                }
                
            };
            for (auto v: g[0]) dfs2(v, 0);
            return res;
        };

        long long ans = 0;
        for (int i=1; i<=20; i++) ans += calc(i);
        return ans / 2;
    }
};