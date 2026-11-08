#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        const int full = (1 << 10) - 1;
        const int mod = 1e9 + 7;
        int n = par.size()        ;
        vector g(n, vector<int>());
        for (int i=1; i<n; i++) {
            g[par[i]].emplace_back(i);
        }

        auto check = [](int mask, int val) -> int {
            int new_mask = mask;
            while (val) {
                if (new_mask & (1 << (val%10))) return mask;
                new_mask |= 1 << (val%10);
                val /= 10;
            }
            return new_mask;
        };

        int ans = 0;
        auto dfs = [&](this auto&& dfs, int u) -> vector<int> {
            vector<int> cur = {vals[u]};
            // 启发式合并
            for (int v : g[u]) {
                auto child = dfs(v);
                if (cur.size() < child.size()) swap(cur, child);
                for (int x : child) {
                    auto it = ranges::lower_bound(cur, x);
                    if (it == cur.end() || *it != x)
                        cur.insert(it, x);
                } 
                // cur.insert(cur.end(), child.begin(), child.end());
            }              
            unordered_map<int, long long> memo;
            auto max_score = [&] (this auto&& mx, int i, int mask) -> long long {
                if (i < 0 || mask == full) return 0LL;
                int key = mask << 10 | i;
                if (memo.count(key)) return memo[key];
                int new_mask = check(mask, cur[i]);
                if (new_mask == mask) return memo[key] = mx(i-1, mask);
                return memo[key] = max(mx(i-1, mask), cur[i] + mx(i-1, new_mask));
            };
            ans = (max_score(cur.size()-1, 0) + ans) % mod;
            return cur;
        };
        dfs(0);
        return ans;
    }
};