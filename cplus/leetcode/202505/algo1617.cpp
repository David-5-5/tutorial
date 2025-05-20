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

    vector<int> countSubgraphsForEachDiameter2(int n, vector<vector<int>>& edges) {
        // 参考题解 - Floyd - 枚举任意两点的直径
        vector<vector<int>> g(n);
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        for (auto e: edges) {
            int u = e[0]-1, v = e[1] - 1;
            g[u].emplace_back(v), g[v].emplace_back(u);      
            dist[u][v] = 1, dist[v][u] = 1;
        }

        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }

        // Floyd algo 
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) for (int k = 0; k < n; k++) {
            if (dist[j][i] != INT_MAX && dist[i][k] != INT_MAX) 
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);    
        }

        // 检查 u 是否可以加入 x，y 为直径的子树中
        auto dfs = [&](this auto&& dfs, int u, int fa, int x, int y) -> int {
            if (dist[u][x] > dist[x][y] || dist[u][y] > dist[x][y]) return 1;
            if ((dist[u][y] == dist[x][y] && u < x) || (dist[u][x] == dist[x][y] && u < y)) return 1;
            
            int res = 1;
            for (auto v: g[u]) {
                if (v == fa) continue;
                res *= dfs(v, u, x, y);
            }
            if (dist[u][x] + dist[u][y] > dist[x][y]) res ++;

            return res;
        };

        vector<int> ans(n-1);
        for (int i = 0; i < n-1; ++i) for (int j = i+1; j < n; ++j) {
            ans[dist[i][j] - 1] += dfs(i, -1, i, j);
        }
        return ans; 
    }    
};