#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路：Dijkstra 算法
class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        // 自行解答
        vector<vector<int>> g(n+1);
        for (auto& e: edges) {
            g[e[0]].emplace_back(e[1]); g[e[1]].emplace_back(e[0]);
        }
        
        vector<int> q, dis(n+1, INT_MAX/2); dis[1] = 0; q.push_back(1);
        auto min_dis = [&]() -> void {
            int d = 0;
            for (int d=1; ;d++) {
                vector<int> nxt;
                for (auto u: q) {
                    if (u == n) return;
                    for (auto& v: g[u])   if (dis[v] > d) {
                            dis[v] = d; nxt.push_back(v);
                    }
                }
                q = move(nxt);
            }
        };
        min_dis();  // 计算出最短路径

        auto check = [&] (this auto&& check, int u) -> bool {
            vector<int> prev;
            for (auto& v: g[u]) {
                if (dis[v] + 1 == dis[u]) prev.emplace_back(v); // u 的前一个节点
                if (dis[v] == dis[u]) return true;              // v 和 u 距离相同，使得 u 的距离仅增加 1
            }
            for (auto & v: prev) if (check(v)) return true;

            return false;
        }; // 最短路径上是否存在环，使得路径增加 1

        int cnt = dis[n], ans = 0;
        if (check(n))  cnt += 1;        // 路径加 1
        else cnt += 2;                  // 路径加 2，即从上个节点再回到 n 节点

        for (int i=0; i<cnt; i++) {
            if (ans / change % 2) ans += change-(ans%change);
            ans += time;
        }
        return ans;  
    }

  
};