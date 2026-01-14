#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        // 自行解答 dfs
        int n = bombs.size();
        vector<vector<int>> g(n);
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
            if (i == j) continue;
            int xi = bombs[i][0], yi = bombs[i][1], xj = bombs[j][0], yj = bombs[j][1], r = bombs[i][2];
            if (1LL * (xi-xj) * (xi-xj) + 1LL * (yi-yj) * (yi-yj) <= 1LL* r * r) g[i].push_back(j);
        }

        int ans = 0;
        for (int i=0; i<n; ++i) {
            vector<int> vis(n);
            auto dfs = [&](this auto&& dfs, int u) -> int {
                int res = 1; vis[u] = true;
                for (auto & v: g[u]) {
                    if (vis[v]) continue;
                    res += dfs(v); 
                }
                return res;
            };
            ans = max(ans, dfs(i));
        }

        return ans;    
    }
};