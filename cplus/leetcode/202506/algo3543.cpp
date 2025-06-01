#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        // 参考题解 畏难了，这题应该会的，动态规划暴力就可以
        vector<vector<pair<int, int>>> g(n);
        for (auto e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);   // 有向图
        }

        int ans = -1;

        unordered_map<int, bool> visited;
        auto dfs = [&](this auto&& dfs, int u, int l, int s) -> void {
            if (l == k) ans = max(ans, s);
            int mask = u << 19 | l << 10  | s;
            
            if (visited.count(mask)) return;
            for (auto& [v, w]: g[u]) {
                if (w + s < t) dfs(v, l+1, w+s);
            }
            visited[mask] = true;
        };

        for (int u=0; u<n; ++u) dfs(u, 0, 0);

        return ans;
    }
};