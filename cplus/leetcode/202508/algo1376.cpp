#include <bits/stdc++.h>
using namespace std;

// 一般树 - 3.2 自顶向下 DFS
class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        // 自行解答
        vector<vector<int>> g(n, vector<int>());
        for (int i=0; i<n; i++) {
            if (manager[i] == -1) continue;
            g[manager[i]].push_back(i);
        }
        
        auto dfs = [&](this auto&& dfs, int u, int fa) -> int {
            int cur = 0;
            for (auto& v: g[u] ) {
                if (v == fa) continue;
                cur = max(cur, dfs(v, u));
            }
            return cur+informTime[u];
        };
        return dfs(headID, -1);   
    }
};