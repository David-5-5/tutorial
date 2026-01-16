#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.2 广度优先搜索（BFS）
class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        // 自行解答 bfs 计算出节点 0 和其他各节点的距离，根据距离计算出最后发送的消息
        int n = patience.size();
        vector<int> dist(n, INT_MAX/2); vector<vector<int>> g(n);
        for (auto& e: edges) {
            g[e[0]].emplace_back(e[1]); g[e[1]].emplace_back(e[0]);
        }

        dist[0] = 0; vector<int> q = {0}; int step = 0;
        while (!q.empty()) {
            step ++;
            vector<int> nxt;
            for (auto& u : q) for (auto& v: g[u]) {
                if (step < dist[v]) {
                    dist[v] = step; nxt.emplace_back(v);
                }
            }
            q = move(nxt);
        }

        int ans = 0;
        for (int i=1; i<n; ++i) {
            auto & d = dist[i], & p  = patience[i];
            ans = max(ans, 1 + (d * 2 - 1)/p * p + d * 2);
        }
        return ans;
    }
};