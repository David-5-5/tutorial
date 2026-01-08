#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 自行解答 拓扑排序
        vector<int> degree(numCourses); vector<vector<int>> g(numCourses);
        for (auto& e : prerequisites)  {
            g[e[1]].emplace_back(e[0]); degree[e[0]] ++;
        }
        deque<int> nodes;
        for (int i=0; i<numCourses; ++i) if (degree[i] == 0)
            nodes.push_back(i);     // toplogy sort degree == 0
        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop_front();
            for (auto v: g[u]) {
                degree[v] --; if (degree[v] == 0) nodes.push_back(v);
            }
        }

        return all_of(degree.begin(), degree.end(), [](int x) {
            return x == 0;
        });
    }
};