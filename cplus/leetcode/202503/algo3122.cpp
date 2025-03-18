#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> cnt(m, vector<int>(10));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                cnt[j][grid[i][j]] += 1;
            }
        }

        vector<vector<int>> memo(m, vector<int>(11, -1));
        auto dfs = [&](this auto&& dfs, int i, int v) -> int {
            if (i == m) return 0;
            
            auto& res = memo[i][v];
            if (res != -1) return res;
            res = n + dfs(i+1, 10);    // 全部都该
            for (int nv=0; nv<10; nv++) {
                if (nv == v) continue;
                res = min(res, n - cnt[i][nv] + dfs(i+1, nv));
            }
            return res;
        };

        return dfs(0, 10);  
        
    }

    
};