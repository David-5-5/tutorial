#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.2 在拓扑序上 DP
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        // 自行解答 toplogy sort
        int n = quiet.size(); vector<int> ans(n);
        iota(ans.begin(), ans.end(), 0);                //  min quiet is self by default

        vector<vector<int>> g(n); vector<int> degree(n);
        for (auto e: richer) {
            g[e[0]].emplace_back(e[1]); degree[e[1]]++; // e[0] > e[1] richer
        }

        deque<int> q; for (int i=0; i<n; i++) if (degree[i] == 0) q.push_back(i);
        while (!q.empty()) {
            auto u = q.front(); q.pop_front();
            for (auto & v: g[u]) {
                // 用父节点的最小 quiet 值，更新子节点
                if (quiet[ans[v]] > quiet[ans[u]]) ans[v] = ans[u];
                degree[v] --; if (degree[v] == 0) q.push_back(v);
            }
        }
        return ans;  
    }
};