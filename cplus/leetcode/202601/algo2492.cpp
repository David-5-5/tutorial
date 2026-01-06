#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // 自行解答
        vector<vector<pair<int, int>>> g(n);
        for (auto e : roads) {
            int u = e[0]-1 , v = e[1]-1 , w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        vector<bool> vis(n); int ans = INT_MAX;

        auto dfs = [&](this auto&& dfs, int u) -> void {
            int res = INT_MAX / 2;
            for (auto & [v, w]: g[u]) {
                ans = min(ans, w);
                if (vis[v]) continue;
                vis[v] = true; dfs(v); 
            }
        };
        dfs(0);
        return ans;
    }
};