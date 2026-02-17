#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<int> dis(n, INT_MAX); dis[0] = 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto& e: edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]*2);
        }

        // 今天犯了一个错误，写成这样了 priority_queue<pair<int, int>> pq;
        // Dijkstra 计算最短路径，需要小顶堆 默认却是大顶堆，一直超时
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dis[u]) continue;
            if (u == n-1) return d;
            for (auto & [v, w]: g[u]) {
                if (d+w < dis[v]) {
                    dis[v] = d+w; pq.emplace(dis[v], v);
                }
            }
        }
        return -1;

    }
};