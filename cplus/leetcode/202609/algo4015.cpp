#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long weightedSum(vector<int>& parent, vector<int>& nums) {
        int n = parent.size();
        vector g(n, vector<int>());

        for (int i=0; i<n; i++) {
            auto& p = parent[i];
            if (p != -1) {
                g[p].emplace_back(i);
            }
        }

        auto get_height = [&](this auto&& f, int u) -> int {
            int height = 0;
            for (auto & v: g[u]) {
                height = max(height, f(v));
            }

            return height + 1;
        };

        auto h = get_height(0);

        auto dfs = [&](this auto&& dfs, int u, int d) -> long long {
            long long res = 1LL * nums[u] * (h - d);
            for (auto & v :g[u]) {
                res += dfs(v, d+1);
            }

            return res;
        };

        return dfs(0, 0);

    }


};