#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        // 自行解答 
        vector<vector<pair<int, double>>> g(n); int m = edges.size();
        vector<double> probs(n); probs[start_node] = 1.0;

        for (int i=0; i<m; ++i) {
            auto u = edges[i][0], v = edges[i][1]; auto p = succProb[i];
            g[u].emplace_back(v, p); g[v].emplace_back(u, p);
        }
        
        // 默认是大顶堆
        priority_queue<pair<double, int>> q; q.emplace(probs[start_node], start_node);
        while (!q.empty()) {
            auto [up, u] = q.top(); q.pop();

            for (auto [v, vp]: g[u]) {
                if (vp * up > probs[v]) {
                    probs[v] = vp * up; q.emplace(probs[v], v);
                }
            }
        }

        return probs[end_node];    
    }
};