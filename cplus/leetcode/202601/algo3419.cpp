#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        // 参考题解 - DFS + 二分 
        // ###############################################################
        // 关键 threshold 多余，每个节点的出度<threshold。题目是所有节点到达
        // 节点 0。这样将有向图反转，则从节点 0 到达所有节点。这样入度 < threshold
        // 就可以了，到达所有节点，这样每个节点的入度为 1，就可以到达所有节点了
        // 而题目保证 threshold >= 1。
        // 剩下来的就是找到最大权值的最小值，用DFS + 二分 或 单源最短路：Dijkstra
        // ###############################################################
        // 也是被 threshold 扰乱了思路
        if (edges.size() < n-1) return -1;

        vector<vector<pair<int, int>>> g(n); int mx = 0;
        for (auto e: edges) {
            g[e[1]].emplace_back(e[0], e[2]);
            mx = max(mx, e[2]);
        }

        vector<int> vis(n);
        auto check = [&] (int limit) -> bool {
            int left = n; 
            auto dfs = [&](this auto&& dfs, int u) -> void {
                vis[u] = limit; left --;
                for (auto [v, w]: g[u]) {
                    if (w <= limit && vis[v]!=limit) dfs(v);
                }
            };
            dfs(0);
            return left == 0;
        };

        int left = 0, right = mx + 1;
        while (left + 1 < right) {
            auto mid = (left + right) / 2;
            (check(mid)?right:left) = mid;
        }
        return right>mx?-1:right;
    }

    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        // 单源最短路：Dijkstra, 用最小的权值，代替最短路径
        if (edges.size() < n-1) return -1;

        vector<vector<pair<int, int>>> g(n);
        for (auto e: edges) {
            g[e[1]].emplace_back(e[0], e[2]);
        }

        vector<bool> vis(n); int left = n; int mx = 0;
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<>> pq;
        pq.emplace(0, 0);
        while (!pq.empty() && left) {
            auto [d, u] = pq.top(); pq.pop();
            if (vis[u]) continue;
            vis[u] = true; left --; mx = max(mx, d);
            for (auto [v, w]: g[u]) {
                pq.emplace(w, v);
            }
        }

        return left == 0?mx : -1;
    }

};