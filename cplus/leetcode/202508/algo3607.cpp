#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 专题 - 离线算法
class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        // 自行解答 图的连通块
        vector<vector<int>> g(c+1);
        for (auto& e : connections) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        vector<int> conn_id(c+1);
        vector<set<int>> conn;
        // 图的连通块 - dfs - 生成连通块
        vector<bool> vis(c+1);
        auto dfs = [&](this auto&& dfs, int u) -> void {
            vis[u] = true;
            conn.back().insert(u);
            conn_id[u] = conn.size()-1;
            for (int v:g[u]) if (!vis[v]) dfs(v);
        };
        
        for (int u=1; u<c+1; ++u) {
            if (!vis[u]) {
                conn.emplace_back(); dfs(u);
            }
        }
        // 图的连通块 - dfs - 生成连通块

        vector<int> ans;
        for (auto& q: queries) {
            auto type = q[0], x = q[1];
            if (type == 1) {
                if (conn[conn_id[x]].size() > 0)
                    if (conn[conn_id[x]].count(x)) ans.push_back(x);
                    else ans.push_back(*conn[conn_id[x]].begin()); // 返回连通块中最小的点
                else ans.push_back(-1);
            } else {
                if (conn[conn_id[x]].count(x)) conn[conn_id[x]].erase(x); 
            }
        }
        return ans; 
    }

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        // 参考题解 - 堆 + 懒删除 - 堆的性能更优
        vector<vector<int>> g(c+1);
        for (auto& e : connections) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<int> conn_id(c+1);
        vector<priority_queue<int, vector<int>, greater<>>> conn;   
        // 图的连通块 - dfs - 生成连通块
        vector<bool> vis(c+1);
        auto dfs = [&](this auto&& dfs, int u) -> void {
            vis[u] = true;
            conn.back().push(u);
            conn_id[u] = conn.size()-1;
            for (int v:g[u]) if (!vis[v]) dfs(v);
        };
        
        for (int u=1; u<c+1; ++u) {
            if (!vis[u]) {
                conn.emplace_back(); dfs(u);
            }
        }
        // 图的连通块 - dfs - 生成连通块

        vector<bool> offlined(c+1);
        vector<int> ans;
        for (auto& q: queries) {
            auto type = q[0], x = q[1];
            if (type == 1) {
                if (!offlined[x]) ans.push_back(x);
                else {
                    while (!conn[conn_id[x]].empty() && offlined[conn[conn_id[x]].top()]) conn[conn_id[x]].pop();
                    if (!conn[conn_id[x]].empty()) ans.push_back(conn[conn_id[x]].top());
                }
            } else {
                offlined[x] = true;
            }
        }
        return ans; 
    }
};