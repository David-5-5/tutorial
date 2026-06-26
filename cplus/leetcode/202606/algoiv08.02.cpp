#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
        // 基本功
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector seen(m, vector<bool>(n));

        vector<vector<int>> ans;

        auto dfs = [&](this auto&& dfs, int r, int c) -> bool {
            if (r >= m || c >= n || obstacleGrid[r][c] == 1 || seen[r][c]) return false;

            seen[r][c] = true;            
            if ((r == m-1 && c == n-1) || dfs(r+1, c) || dfs(r, c+1)) {
                ans.push_back({r, c}); return true;
            }

            return false;
        };
        dfs(0, 0);
        reverse(ans.begin(), ans.end());
        return ans;     
    }
};