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
                not_choose += nc;       // 先都不选 不选 w
                int d = c + w - nc;     // d 为选择和 x 的，需要删除 y 与子节点的一条边
                if (d > 0) inc.push_back(d);    // 增量小于 0 不需要选择，放弃 w
            }
            
            // 核心在这里，代码很简单，不太好理解
            // 对于节点 x，
            //   不选择与父节点有边，则选择与其子节点 y 选择增量最大的 k 条边
            //   选择与父节点有边,   则选择与其子节点 y 选择增量最大的 k - 1条边
            ranges::sort(inc, greater());   // 从大到小排序 
            for (int i=0; i<min((int)inc.size(), k-1); ++i) not_choose += inc[i];
            long choose = not_choose;
            if (inc.size() >= k)  not_choose += inc[k - 1];

            return {not_choose, choose};
        };

        return dfs(0, -1).first;
    }
};