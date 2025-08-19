#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    int countGoodNodes(vector<vector<int>>& edges) {
        // 自行解答
        int ans = 0, n = edges.size() + 1;
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        auto dfs = [&] (this auto&& dfs, int u, int fa) -> int {
            int cnt = 1; set<int> diff;
            for (auto& v: g[u]) {
                if (v == fa) continue;
                auto child = dfs(v, u);
                cnt += child; diff.insert(child);
            }
            if (diff.size()<=1) ans += 1;
            return cnt;
        };

        dfs(0, -1); return ans;
        
    }

    
    int countGoodNodes2(vector<vector<int>>& edges) {
        // 自行解答
        int ans = 0, n = edges.size() + 1;
        vector<vector<int>> g(n, vector<int>());
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        auto dfs = [&] (this auto&& dfs, int u, int fa) -> int {
            int cnt = 1, prev = 0; bool equals = true;
            for (auto& v: g[u]) {
                if (v == fa) continue;
                auto child = dfs(v, u);
                cnt += child; 
                if (equals) {   // 这样写快多了
                    equals = (prev == 0 || prev == child); prev = child;
                }
            }
            if (equals) ans += 1;
            return cnt;
        };

        dfs(0, -1); return ans;
    }    
};