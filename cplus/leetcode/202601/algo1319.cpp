#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        // 自行解答，连通块数 - 1 即为答案
        if (connections.size() + 1 < n) return -1;

        vector<vector<int>> g(n);
        for (auto e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<bool> vis(n);

        auto dfs = [&](this auto&& dfs, int u) -> void {
            for (auto & v: g[u]) {
                if (vis[v]) continue;
                vis[v] = true; dfs(v); 
            }
        };

        int ans = 0;
        for (int i=0; i<n; ++i) {
            if (vis[i]) continue;
            ans += 1;  vis[i] = true; dfs(i);
        }

        return ans - 1;   
    }
};