#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges) {
        // 自行解答
        priority_queue<pair<int,int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dis(n, INT_MAX/2);

        vector<vector<tuple<int, int, int>>> g(n);
        for (auto & e : edges) {
            auto u = e[0], v = e[1], start = e[2], end = e[3];
            g[u].emplace_back(v, start, end);
        }
        
        pq.emplace(0, 0); dis[0] = 0;
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();   // pq 内容变更

            for (auto& [v, start, end]: g[u]) {
                if (d > end) continue;
                if (max(start,d) + 1 < dis[v]) {
                    dis[v] = max(start,d) + 1; pq.emplace(dis[v], v); 
                }
            }
        } 

        return dis[n-1]==INT_MAX/2?-1:dis[n-1];     

    }
};