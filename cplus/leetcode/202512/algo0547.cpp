#include <bits/stdc++.h>
using namespace std;

// 图论算法 一、图的遍历 1.1 深度优先搜索（DFS）
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        // 自行解答 dfs 求连通块
        int n = isConnected.size(); vector<bool> vis(n);
        
        auto dfs = [&](this auto&& dfs, int i) -> void {
            for (int j=0; j<n; ++j) {
                if (i == j || vis[j] || isConnected[i][j] == 0) continue;
                vis[j] = true; dfs(j);
            }
        };

        int ans = 0;
        for (int i=0; i<n; i++) {
            if (!vis[i]) {
                ans ++; dfs(i);
            }
        }
        return ans;   
    }
};