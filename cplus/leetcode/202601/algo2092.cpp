#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // 自行解答
        vector<int> vis(n, INT_MAX);
        vector<unordered_map<int, set<int>>> g(n);  // 找到合适的数据结构
        for (auto & m: meetings) {
            auto& x = m[0], y = m[1], t= m[2];
            g[x][y].insert(t); g[y][x].insert(t);
        }

        vis[0] = 0; vis[firstPerson] = 0;
        auto dfs = [&](this auto && dfs, int u) -> void {
            for (auto& [v, t]: g[u]) {
                auto it = t.lower_bound(vis[u]);    // u 将秘密传给 v 的最小时间
                if (it!=t.end() && vis[v] > *it) {
                    vis[v] = *it;
                    dfs(v);
                }
            }
        };
        dfs(0); dfs(firstPerson);
        vector<int> ans;
        for (int i=0; i<n; ++i) if (vis[i] < INT_MAX) ans.push_back(i);
        return ans;  
    }
};