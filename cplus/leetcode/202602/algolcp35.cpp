#include <bits/stdc++.h>
using namespace std;

// 图论算法 三、最短路 3.1 单源最短路： Dijkstra 算法
class Solution {
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        // 自行解答 - 参考豆包的提示
        // 起先有这个思路，但是不确定代码的细节，没有继续深入。
        // 大致思路是充不同电量到下个节点 (u, v, w),  
        // 节点 u 充 w <= charges <= cnt ，起初剩余电量为 0 的情况
        //     v 剩余 0 <= left <= cnt - w 电量，剩余电量在后续免费使用
        //     因此 v -> v1 节点后， 剩余电量无需计算时间
        // 因此 dis[u][r] 表示节点 u 剩余电量 r 时的最少路径
        //      优先队列中的元素为 tuple<dis[u][r], u, r>
        int n = charge.size(); vector<vector<pair<int, int>>> g(n);
        for (auto e: paths) {
            g[e[1]].emplace_back(e[0], e[2]);
            g[e[0]].emplace_back(e[1], e[2]);
        }
        
        vector dis(n, vector<int>(cnt, INT_MAX));   // 带到节点的剩余电量最多为 cnt - w
        dis[start][0] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        
        pq.emplace(0, start, 0);
        while (!pq.empty()) {
            auto [cost, u, rem] = pq.top(); pq.pop();
            if (cost > dis[u][rem]) continue;                       // 剪枝
            for (auto &[v, w] : g[u]) {
                for (int r = max(rem-w, 0); r<=cnt-w; r++) {       // r 表示从 u 充电剩余到 v 的电量
                    auto n_cost = cost + w + max(0, w + r - rem) * charge[u]; // 在 u 节点充电时间
                    if (n_cost < dis[v][r]) {
                        dis[v][r] = n_cost; pq.emplace(n_cost, v, r);
                    }
                }
            }
        }

        return ranges::min(dis[end]);
    }
};