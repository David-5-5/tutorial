#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        // 自行解答 复习 2026.1.31
        vector<vector<pair<int, int>>> g(n);
        for (auto e: edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]);
        }

        vector<int> dis(n, INT_MAX); dis[0] = 0;
        priority_queue<pair<long long, int>, vector<pair<long long,int>>, greater<>> pq;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dis[u]) continue;
            for (auto& [v, w]: g[u]) {
                if (dis[v] > w + d + 1) {       // w + d + 1 <= maxMoves 没有必要
                    dis[v] = w + d + 1;         // 距离需要包括 v
                    pq.emplace(dis[v], v);
                }
            }
        }
        
        int ans = 0;
        for (int i=0; i<n; ++i) if (dis[i] <= maxMoves)  ans ++;
        for (auto& e:edges) {
            auto & u = e[0], & v = e[1], & w = e[2];
            auto left = max(0, maxMoves-dis[u]), right = max(0, maxMoves-dis[v]);
            ans += min(w, left + right);
        }
        return ans;
    }
};