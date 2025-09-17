#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.7 搜索
class Solution {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        // 自行解答
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        int ans = 0, m = grid.size(), n = grid[0].size();

        auto dfs = [&] (this auto&& dfs, int i, int j) -> int {
            if (grid[i][j] == 0) return 0;
            
            int res = 0, ij = grid[i][j]; 
            for (int k=0; k<4; ++k) {
                auto i_ = i+dirs[k][0], j_ = j+dirs[k][1];
                if (i_>=0 && i_<m && j_>=0 && j_<n) {
                    grid[i][j] = 0;
                    res = max(res, dfs(i_, j_));
                    grid[i][j] = ij;
                }
            }
            return ij + res;
        };

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) 
            ans = max(ans, dfs(i, j));
        
        return ans;
        
    }
};