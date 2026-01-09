#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        // 自行解答 拓扑排序
        int n = graph.size();
        vector<vector<int>> g(n); vector<int> degree(n);
        for (int i=0; i<n; ++i) for (auto& j: graph[i]) {
            g[j].push_back(i); degree[i] ++;
        }
        deque<int> nodes; vector<int> ans;
        for (int i=0; i<n; ++i) if (degree[i] == 0)
            nodes.push_back(i);     // toplogy sort degree == 0        
        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop_front(); ans.push_back(u);
            for (auto v: g[u]) {
                degree[v] --; if (degree[v] == 0) nodes.push_back(v);
            }
        }
        sort(ans.begin(), ans.end());
        return ans;   
    }
};