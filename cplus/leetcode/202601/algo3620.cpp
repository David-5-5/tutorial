#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.2 在拓扑序上 DP
class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        // 参考题解 二分 + 记忆化搜索
        // 最大最小，!!!怎么就忘了二分呢!!!
        int n = online.size(), l = -1, r = 0;

        vector<vector<pair<int, int>>> g(n);
        for (auto& e: edges) {
            if (online[e[0]] && online[e[1]])
                g[e[0]].emplace_back(e[1], e[2]);
            r = max(r, e[2]);
        }
        r ++;   // （l, r) 开区间

        vector<long long> memo(n, -1);
        while (l + 1 < r) {
            auto check = [&](int lower) -> bool {
                ranges::fill(memo, -1);
                auto dfs = [&](this auto&& dfs, int u) -> long long { // cost
                    if (u == n-1) return 0;
                    auto & res = memo[u];
                    if (res != -1) return res;
                    res = LLONG_MAX / 2;
                    for (auto& [v, c]: g[u]) {
                        if (c >= lower)
                            res = min(res, dfs(v) + c);
                    }
                    return res;
                };
                return dfs(0) <= k;
            };
   
            int mid = (l + r) / 2;
            (check(mid)? l : r) = mid;
        }
        return l;
    }

};