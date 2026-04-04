#include <bits/stdc++.h>
using namespace std;

// 同 79
class Solution {
public:
    bool wordPuzzle(vector<vector<char>>& grid, string target) {
        const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int m = grid.size(), n = grid[0].size();

        vector<vector<bool>> vis(m, vector<bool>(n));

        auto dfs = [&](this auto&& dfs, int i, int j, int cnt) -> bool {            
            if (grid[i][j] != target[cnt]) return false;
            cnt ++;
            if (cnt == target.length()) return true;
            vis[i][j] = true;
            
            for (int k=0; k<4; ++k) {
                auto i_ = i + dirs[k][0], j_ = j + dirs[k][1];
                if (i_ >= 0 && i_<m && j_>=0 && j_<n && !vis[i_][j_] && dfs(i_, j_, cnt))
                    return true;

            }
            vis[i][j] = false;
            return false;
        };

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            if (dfs(i, j, 0))  return true;
        }
        return false;        
    }
};