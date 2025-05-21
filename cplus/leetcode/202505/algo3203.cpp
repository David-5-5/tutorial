#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 12.1 树的直径
class Solution {
public:
    // 参考题解，知道树的直径，但是两个树相连的最小的直径没有思路
    int diameter(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> g(n, vector<int>());
        for (auto& e: edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        
        int dia = 0;
        auto dfs = [&](this auto&& dfs, int i, int fa) ->int {
            int max_len = 0;        // 当前节点的最长子树路径
            for (auto& j : g[i]) {
                if (j == fa) continue;
                int sub_len = 1 + dfs(j, i);
                dia = max(dia, sub_len + max_len);
                max_len = max(max_len, sub_len);
            }
            return max_len;
        };

        dfs(0, -1);
        return dia;
    }
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int dia1 = diameter(edges1), dia2 = diameter(edges2);
        // 两个树相连最小直径为 max(d1, d2, (d1+1)/2 + (d2+1)/2 + 1)
        return max(dia1, max(dia2, (dia1+1)/2 + (dia2+1)/2 + 1));
    }
};