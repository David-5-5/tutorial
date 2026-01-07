#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // 参考题解， 逻辑关系
        vector<vector<int>> g(n);
        for (auto& e : invocations)  g[e[0]].emplace_back(e[1]);

        vector<bool> is_suspicious(n);

        auto dfs = [&](this auto&& dfs, int u) -> void {
            is_suspicious[u] = true;
            for (auto & v: g[u]) {
                if (is_suspicious[v]) continue;
                dfs(v); 
            }
        };
        dfs(k);
        for (auto& e : invocations) if (!is_suspicious[e[0]] && is_suspicious[e[1]]) {
            vector<int> ans(n); iota(ans.begin(), ans.end(), 0); return ans;
        }
        vector<int> ans;
        for (int i=0; i<n; i++) if (!is_suspicious[i]) ans.push_back(i);         
        return ans;
    }
};