#include <bits/stdc++.h>
using namespace std;

// 一、网格图 DFS
class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        // 自行解答，dfs 求每个连通块个数
        int m = land.size(), n = land[0].size();
        vector vis(m, vector<bool>(n, false));

        auto dfs = [&](this auto&& dfs, int x, int y) -> int {
            if (x <0 || x >=m || y<0 || y >= n || vis[x][y] || land[x][y]) return 0;
            vis[x][y] = true;
            int res = 1;
            res += dfs(x+1, y); res += dfs(x-1, y); res += dfs(x, y-1); res += dfs(x, y+1);
            res += dfs(x-1, y-1); res += dfs(x-1, y+1); res += dfs(x+1, y-1); res += dfs(x+1, y+1);
            return res;
        };

        vector<int> ans;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (vis[i][j] || land[i][j]) continue;
            int values = dfs(i, j);

            ans.emplace_back(values);
        }
        sort(ans.begin(), ans.end());
        return ans;    
    }
};