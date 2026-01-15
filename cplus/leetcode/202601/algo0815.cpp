#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.2 广度优先搜索（BFS）
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        // 自行解答 
        if (source == target) return 0;

        int n = routes.size();
        for (auto& r: routes) sort(r.begin(), r.end());
        
        // 有序队列双指针判读是否存在相同元素 O(min(m, n))
        auto isInter = [] (const vector<int>& v1, const vector<int>& v2) -> bool {
            auto it1 = v1.begin(), it2 = v2.begin();
            while (it1 != v1.end() && it2 != v2.end()) {
                if (*it1 == *it2) return true;
                *it1 < *it2 ? ++it1 : ++it2;
            }
            return false;
        };

        // 有序队列查找元素 O(logN)
        auto count = [] (vector<int>& arr, int val) -> bool {
            auto it = ranges::lower_bound(arr, val);
            return it!=arr.end() && *it == val;
        };

        vector<vector<int>> g(n);
        for (int u=0; u<n-1; ++u) for (int v=u+1; v<n; ++v) {
            if (isInter(routes[u], routes[v])) {
                g[u].emplace_back(v); g[v].emplace_back(u);
            }
        }

        vector<int> q; int step = 0; vector<bool> vis(n);
        for (int i=0; i<n; ++i) if (count(routes[i], source)) {
            q.push_back(i); vis[i] = true;
        }

        while (!q.empty()) {
            vector<int> nxt; step ++;
            for (auto& u: q) {
                if (count(routes[u], target)) return step;
                for (auto & v :g [u]) {
                    if (vis[v]) continue;
                    nxt.push_back(v); vis[v] = true;
                }
            }
            q = move(nxt);
        }
        
        return -1;
    }
};