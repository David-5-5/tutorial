#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        // 自行解答 基础
        vector<vector<int>> ans; int n = graph.size();

        auto dfs = [&](this auto&& dfs, int u, vector<int>& path) -> void {
            if (u == n-1) {
                ans.push_back(path); return;
            }
            for (auto & v : graph[u]) {
                path.push_back(v);
                dfs(v, path);
                path.pop_back();
            }
        };
        
        vector<int> path = {0};
        dfs(0, path);        
        return ans;
    }
};