#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 自行解答，还能默写出 Dijkstra 算法 ！！！
        priority_queue<pair<int,int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dis(n, INT_MAX/2);
        vector<vector<pair<int, int>>> g(n);

        pq.emplace(0, k-1); dis[k-1] = 0;
        for (auto & time : times) {
            auto u = time[0]-1, v = time[1]-1, t = time[2];
            g[u].emplace_back(v, t);
        }
        
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();   // pq 内容变更 不能使用auto &[d, u]

            for (auto& [v, t]: g[u]) {
                if (d + t < dis[v]) {
                    dis[v] = d + t; pq.emplace(dis[v], v); 
                }
            }
        }

        auto mx = ranges::max(dis);
        return mx == INT_MAX/2?-1:mx;   

    }
};