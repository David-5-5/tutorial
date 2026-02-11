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

    int secondMinimum2(int n, vector<vector<int>>& edges, int time, int change) {
        // 参考题解，题解的思路是建立二维 dis 数组 vector = dis(n+1, vector<int>(2, INT_MAX));
        // 这样每个节点仅经过两次
        vector<vector<int>> g(n+1);
        for (auto& e: edges) {
            g[e[0]].emplace_back(e[1]); g[e[1]].emplace_back(e[0]);
        }
        deque<pair<int, int>> q = {{1,0}};
        vector dis(n+1, vector<int>(2, INT_MAX)); dis[1][0] = 0;
        while (dis[n][1] == INT_MAX) {
            auto [u, d] = q.front(); q.pop_front();
            for (auto& v: g[u]) {
                if (dis[v][0] > d+1) {
                    dis[v][0] = d+1; q.emplace_back(v, dis[v][0]);
                } else if (dis[v][0] < d+1 && dis[v][1] > d+1) {
                    // 最初 dis[v][0] < d+1 &&  这个条件遗漏了
                    // 按照题意次小的路径，必须是严格大于最小的路径
                    // 因此当第二次到达节点 v 时，必须设置一个大于 dis[v][0] 的值
                    dis[v][1] = d+1; q.emplace_back(v, dis[v][1]);
                }
            }
        }

        int ans = 0;
        for (int i=0; i<dis[n][1]; i++) {
            if (ans / change % 2) ans += change-(ans%change);
            ans += time;
        }
        return ans;
    }    
};