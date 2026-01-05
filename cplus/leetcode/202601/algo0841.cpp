#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // 自行解答 基础
        int n = rooms.size(); vector<bool> vis(n);
        auto dfs = [&](this auto&& dfs, int u) -> void {
            for (auto& v : rooms[u]) {
                if (vis[v]) continue;
                vis[v] = true; dfs(v);
            }
        };
        vis[0] = true; dfs(0);
        return all_of(vis.begin(), vis.end(), [](bool x){return x;});
    }
};