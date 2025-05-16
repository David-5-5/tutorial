#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.1 树的直径
class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        // 参考题解 - 动态规划
        vector<vector<int>> g(n);
        for (auto e: edges) {
            int u = e[0]-1, v = e[1] - 1;
            g[u].emplace_back(v), g[v].emplace_back(u);        
        }

        auto dfs = [&](this auto&& dfs, int root, int& mask, int& diameter) -> int {
            int max_len = 0;        // 当前节点的最长子树路径
            mask &= ~(1 << root);
            for (auto& j : g[root]) {
                if ((mask & (1 << j)) == 0)  continue;
                // mask &= ~ (1 << j);
                int sub_len = 1 + dfs(j, mask, diameter);
                diameter = max(diameter, sub_len + max_len);
                max_len = max(max_len, sub_len);
            }
            return max_len;            
        };

        vector<int> ans(n-1);
        for (int i = 1; i < (1 << n); ++i) {
            int root = 32 - __builtin_clz(i) - 1;   // 最高非零位为根节点
            int mask = i;
            int diameter = 0;
            dfs(root, mask, diameter);
            // mask != 0 表示图不连通
            if (mask == 0 && diameter) ans[diameter-1] ++;
        }
        return ans;     
    }
};