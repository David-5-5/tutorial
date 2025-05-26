#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.2 树上最大独立集
class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // unordered_map<int, int> cache; // !!!时间超时!!!
        vector cache(n, vector<array<long, 2>>(k, {LONG_LONG_MIN, LONG_LONG_MIN}));
        auto dfs = [&](this auto&& dfs, int u, int fa, int d, int rev) {
            auto& res = cache[u][d][rev];
            if (res != LONG_LONG_MIN) {
                return res;
            }

            res = rev ? -nums[u] : nums[u];
            for (int v : g[u]) {
                if (v == fa) continue;
                res += dfs(v, u, max(d - 1, 0), rev);
            }

            if (d == 0) {
                rev ^= 1;
                long res1 = rev ? -nums[u] : nums[u];
                for (int v : g[u]) {
                    if (v == fa) continue;
                    res1 += dfs(v, u, k - 1, rev);
                }
                res = max(res, res1);
            }
            return res;
        };

        return dfs(0, -1, 0, 0);
        
    }
};