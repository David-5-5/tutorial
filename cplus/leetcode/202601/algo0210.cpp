#include <bits/stdc++.h>
using namespace std;

// 图论算法 二、拓扑排序 2.1 拓扑排序
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> degree(numCourses); vector<vector<int>> g(numCourses);
        for (auto& e: prerequisites) {
            degree[e[0]]++; g[e[1]].emplace_back(e[0]);
        }

        deque<int> q; vector<int> ans;
        for (int i=0; i<numCourses; i++) if (degree[i]==0) q.emplace_back(i);

        while (!q.empty()) {
            auto u = q.front(); q.pop_front();
            ans.push_back(u);
            for (auto& v: g[u])  {
                degree[v] --; if (degree[v] == 0) q.emplace_back(v);
            }
        }
        
        // if (ans.size()==numCourses)return ans;
        // else return{};
        return ans.size()==numCourses?ans:vector<int>();
    }
};