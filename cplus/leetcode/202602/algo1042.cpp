#include <bits/stdc++.h>
using namespace std;

// 图论算法 九、其他
class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        // 自行解答 dfs
        vector g(n, vector<int>());
        for (auto &p : paths) {
            auto u = p[0] - 1, v = p[1] - 1;
            g[u].emplace_back(v); g[v].emplace_back(u);
        }
        vector<int> ans(n); 
    
        for (int i=0; i<n; i++) {
            auto dfs = [&](this auto&& dfs, int u) -> void {
                vector<int> occpied(4);
                for (auto v: g[u]) {
                    if (ans[v]) occpied[ans[v]-1] = 1;
                }
                for (int i=0; i<4; i++) if (occpied[i] == 0) {
                    ans[u] = i + 1; break;
                }
                for (auto v: g[u]) if (!ans[v]) {
                    dfs(v);
                }
            };
            if (ans[i]) continue;
            dfs(i);
        }
        return ans;
    }
};