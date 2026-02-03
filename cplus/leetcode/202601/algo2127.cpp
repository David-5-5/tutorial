#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.3 基环树
class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        // 自行解答 - 基环树 
        // 性能一般，题解应该有更好的写法提升性能
        int n = favorite.size();
        vector<vector<int>> rg(n);  // 反向图
        vector<int> deg(n);

        // 拓扑排序 找出有向图的环。从 度为 0 的节点出发，进行拓扑排序
        for (int u=0; u<n; ++u) {
            auto & v = favorite[u];
            deg[v] ++; rg[v].push_back(u);
        }

        deque<int> q; 
        for (int u=0; u<n; ++u) {
            if (deg[u] == 0) q.push_back(u);
        }
        while (!q.empty()) {
            auto u = q.front(); q.pop_front();
            auto & v = favorite[u];
            deg[v] --; if (deg[v] == 0) q.push_back(v);
        }
        // 最终 度为 1 的节点在环上。

        set<int> in_cycle;  // 存在多个环，记录换上的点 - 估计set 的写法比较慢
        for (int u=0; u<n; ++u) {
            if (deg[u]) in_cycle.insert(u);
        }

        // 分情况讨论 ：
        // 1. 多于两个人的环必须占整个桌子
        // 2. 两个人的环，可以共享同一桌子，同时两个人环，环上的人可以通过
        //    反向建图，找出环外的子树的最大深度
        int ans = 0, cnt_2 = 0;  // cnt_2 所有两个元素的环连接的节点数
        auto dfs = [&] (this auto&& dfs, int u) -> int {
            int res = 0;
            for (auto v: rg[u]) {
                if (deg[v]) continue;        // 环上点忽略
                res = max(res ,dfs(v));      // 实质上求树的最长深度
            }
            return res+1;
        };        

        while (!in_cycle.empty()) {
            int first = *in_cycle.begin();
            int nxt = favorite[first];
            in_cycle.erase(first); in_cycle.erase(nxt);
            if (favorite[nxt] == first) {
                cnt_2 += dfs(first) + dfs(nxt);     // 两个人的环可以共享同一桌子
            } else {
                int cnt = 2; // 多人的环
                while (favorite[nxt] != first) {
                    nxt = favorite[nxt]; cnt ++;
                    in_cycle.erase(nxt);
                }
                ans = max(ans, cnt);    // 不共享，找出最大的环
            }
        }

        return max(ans, cnt_2);
    }

};