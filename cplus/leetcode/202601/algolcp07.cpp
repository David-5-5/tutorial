#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    int numWays(int n, vector<vector<int>>& relation, int k) {
        // 自行解答
        vector<vector<int>> g(n);
        for (auto& e: relation) g[e[0]].push_back(e[1]);

        int ans = 0;
        auto dfs = [&](this auto&& dfs, int u, int p) -> void {
            if (p == k) {
                ans += u == n-1; return;
            }

            for (auto& v: g[u]) dfs(v, p + 1);
        };

        dfs(0, 0); return ans;

    }
};