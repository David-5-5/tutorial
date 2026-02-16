#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        // 参考题解 
        vector<vector<pair<int, int>>> g(n), rg(n);
        for (auto e: edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            rg[e[1]].emplace_back(e[0], e[2]);
        }
        auto distance = [&](int begin, vector<vector<pair<int, int>>>& g) -> vector<long long> {
            vector<long long> dis(n, LLONG_MAX/3); dis[begin] = 0;
            priority_queue<pair<long long, int>, vector<pair<long long,int>>, greater<>> pq;
            pq.emplace(0, begin);
            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dis[u]) continue;
                for (auto& [v, w]: g[u]) {
                    if (dis[v] > w + d) {
                        dis[v] = w + d;
                        pq.emplace(dis[v], v);
                    }
                }
            }
            return dis;
        };

        vector<long long> d1= distance(src1, g), d2 = distance(src2, g), d3 = distance(dest, rg);

        long long ans = LLONG_MAX;
        for (int u=0; u<n; ++u) // 找出离 src1 src2 target 距离最短的点
            ans =  min(ans, d1[u] + d2[u] + d3[u]);

        return ans>=LLONG_MAX/3?-1:ans;
    }
};