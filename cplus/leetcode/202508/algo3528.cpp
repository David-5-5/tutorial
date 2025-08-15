#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {
        // 自行解答
        const int mod = 1e9 + 7;
        int n = conversions.size() + 1;
        vector<int> ans(n, 1);

        vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());
        for (int i=0; i<n-1; i++) {
            auto s = conversions[i][0], t = conversions[i][1],  f = conversions[i][2];
            g[s].push_back({t, f});
        }

        auto dfs = [&](this auto&& dfs, int u) -> void {
            for (auto& [v, f]: g[u] ) {
                ans[v] = ((long)ans[u] * f) % mod;
                dfs(v);
            }
        }; 
        dfs(0);        
        return ans;      

    }
};