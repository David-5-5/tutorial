#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        // 自行解答
        // 构建邻接表
        vector<vector<pair<int, int>>> g(n);
        for (const auto& edge : edges) {
            int u = edge[0] - 1, v = edge[1] - 1, w = edge[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }


        // Dijkstra algo 计算最短路
        // BEGIN TEMPLATE Dijkstra
        // 构建邻接表和算法相关，邻接表元素为(v, w), v 为邻接顶点，w 为 u->v 的权重
        vector<int> dist(n, INT_MAX);
        vector<bool> visited(n, false);
        int start = n - 1;        // 单源起点，这里为 n-1 多数情况下为 0 
        dist[start] = 0;


        // 优先队列
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;
            for (const auto& [v, w] : g[u]) {
                if (!visited[v] && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        // END TEMPLATE Dijkstra

        const int mod = 1e9 + 7;
        vector<int> memo(n, -1); 

        // 记忆化 搜索
        auto dfs = [&](this auto&& dfs, int u) {
            if (u == n - 1) return 1;
            if (memo[u] != -1) return memo[u];

            int res = 0;
            for (const auto& [v, _] : g[u]) {
                if (dist[v] < dist[u]) {
                    res = (res + dfs(v)) % mod;
                }
            }
            return memo[u] = res;
        };

        return dfs(0);        
    }
};