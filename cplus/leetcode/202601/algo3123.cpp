#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        // 自行解答 
        vector<int> dis(n, INT_MAX/2); dis[0] = 0;
        vector<vector<pair<int, int>>> g(n);
        for (auto& e: edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            g[e[1]].emplace_back(e[0], e[2]);
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dis[u]) continue;
            if (u == n-1) break;
            for (auto & [v, w]: g[u]) {
                if (d+w < dis[v]) {
                    dis[v] = d+w; pq.emplace(dis[v], v);
                }
            }
        }
        int m = edges.size(); vector<bool> ans(m);
        if (dis[n-1] == INT_MAX/2) return ans;
        unordered_map<long long, int> e2i;
        auto mask = [&](int u, int v) -> long long {
            if (u > v) swap(u, v);
            return 1LL * u * n + v;
        };

        for (int i=0; i<m; ++i) {
            e2i[mask(edges[i][0], edges[i][1])] = i;
        }
        vector<int> q = {n-1};
        vector<int> vis(n); vis[n-1] = true;       // 重要，不然超时
        while (!q.empty()) {
            vector<int> nxt;
            for (auto u : q ){
                for (auto [v, w]:g[u]) {
                    if (w + dis[v] == dis[u]) {   // 多余 !ans[e2i[mask(u, v)]] && 
                        ans[e2i[mask(u, v)]] = true;
                        if (!vis[v]) {             // 重要
                            vis[v] = true; nxt.emplace_back(v);
                        }
                    }
                }
            }
            q = move(nxt);
        }
        return ans;
    }
};