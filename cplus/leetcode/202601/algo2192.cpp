#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        // 自行解答 bfs and toplogy sort, using set deduplication (去重)
        vector<int> degree(n); vector<vector<int>> g(n);
        for (auto& e : edges)  {
            g[e[0]].emplace_back(e[1]); degree[e[1]] ++;
        }
        vector<set<int>> ancestors(n);
        deque<int> nodes;
        for (int i=0; i<n; ++i) if (degree[i] == 0)
            nodes.push_back(i);     // toplogy sort degree == 0
        
        while (!nodes.empty()) {
            int u = nodes.front(); nodes.pop_front();
            for (auto v: g[u]) {
                degree[v] --; if (degree[v] == 0) nodes.push_back(v);
                ancestors[v].insert(u);
                ancestors[v].insert(ancestors[u].begin(), ancestors[u].end());
            }
        }
        vector<vector<int>> ans(n);
        for (int i=0; i<n; ++i) {
            ans[i].insert(ans[i].end(), ancestors[i].begin(), ancestors[i].end());
        }
        return ans;
    }

    vector<vector<int>> getAncestors2(int n, vector<vector<int>>& edges) {
        // dfs 从 u = 0 ~ n-1 逐一遍历每个点，将点 u 作为祖先节点加入遍历到的每个子节点中
        vector<vector<int>> g(n);
        for (auto& e : edges) g[e[0]].emplace_back(e[1]);
        vector<vector<int>> ans(n); vector<int> vis(n, -1);
        for (int start=0; start<n; ++start) {
            auto dfs = [&](this auto&& dfs, int u) -> void {
                vis[u] = start;
                for (auto& v: g[u]) {
                    if (vis[v] == start) continue;
                    ans[v].push_back(start);
                    dfs(v);
                }
            };
            dfs(start);
        }
        return ans;
        
    }
};