#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<vector<int>>& mat) {

        auto cal = [&](vector<vector<int>>& grid) -> int {
            int m = grid.size(), n = grid[0].size();
            vector<int> suf(n);
            vector dp(m, vector<int>(n));
            for (int j=n-1; j; j--) {
                if (j < n-1) suf[j] = max(suf[j], suf[j+1]);
                for (int i=0; i<m; i++)  {
                    if (grid[i][j] == 1) {
                        if (i == 0 || j == n-1) dp[i][j] = 1;
                        else dp[i][j] = min(dp[i-1][j], min(dp[i][j+1], dp[i-1][j+1])) + 1;
                        suf[j] = max(dp[i][j], suf[j]);
                    }
                }
            }
            for (auto& row : dp) row.assign(n, 0); int ans = 0; int mx_j = 0;
            for (int j=0; j<n-1; j++)  for (int i=0; i<m; i++) {
                
                if (grid[i][j] == 1) {
                    if (i == 0 || j == 0) dp[i][j] = 1;
                    else dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1;
                    mx_j = max(mx_j, dp[i][j]);
                }
                ans = max(ans, min(mx_j, suf[j+1]));
            }
            return ans * ans;
        };
        
        auto transpose = [](vector<vector<int>>& grid) -> vector<vector<int>> {
            int m = grid.size(), n = grid[0].size();
            vector trans(n, vector<int>(m));
            for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
                trans[j][i] = grid[i][j];
            }
            return trans;
        };
        
        auto trans = transpose(mat);
        return max(cal(mat), cal(trans));
    }
};