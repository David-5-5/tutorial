#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.5 其他树形 DP
class Solution {
public:
    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        // 参考题解 动态规划 + 贪心
        int n = edges.size() + 1;
        long sum_w = 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto & e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w), g[v].emplace_back(u, w);
            sum_w += w;
        }

        if (all_of(g.begin(), g.end(), [&](vector<pair<int, int>> to){
                return to.size()<=k;
            }))
            return sum_w;

        auto dfs = [&](this auto&& dfs, int x, int fa) -> pair<long, long> {
            long not_choose = 0;
            vector<int> inc;
            for (auto& [y, w] : g[x]) {
                if (y == fa) continue;
                auto [nc, c] = dfs(y, x);
                not_choose += nc;       // 先都不选
                int d = c + w - nc; 
                if (d > 0) inc.push_back(d);
            }

            ranges::sort(inc, greater());   // 从大到小排序
            for (int i=0; i<min((int)inc.size(), k-1); ++i) not_choose += inc[i];
            long choose = not_choose;
            if (inc.size() >= k)  not_choose += inc[k - 1];

            return {not_choose, choose};
        };

        return dfs(0, -1).first;
    }
};