#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        // 自行解答 c++ int -> long
        const int mod = 1e9 + 7;
        long ans = LLONG_MAX/2;

        vector<vector<pair<int, long>>> g(n);

        for (auto& r : roads) {
            int u = r[0], v= r[1], w = r[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        // 路径数
        vector<int> f(n);
        f[0] = 1;

        vector<long> dist(n, LLONG_MAX);
        dist[0] = 0;
        // 优先队列
        priority_queue<pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>> pq;
        pq.emplace(0, 0);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // if (visited[u]) continue;    // 求最短路径 vis 优化剪枝，提升性能，
            // else visited[u] = true;      // !!!!但对于计数会出错!!!!
            if(d > dist[u]) continue;       // 已经出队列 作用同 visited

            for (const auto& [v, w] : g[u]) {
                
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                    f[v] = f[u];
                } else if (dist[v] == dist[u] + w) {
                    f[v] = (f[v] + f[u]) % mod;
                }
            }
        }

        return f[n-1];
    }
};