#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  分组背包
class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int m = mat.size(), n = mat[0].size();

        // 特殊情况
        int mn = 0, mx = 0;
        for (int i=0; i<m; i++) {
            mn += ranges::min(mat[i]);
            mx += ranges::max(mat[i]);
        }
        if (mn > target) return mn - target;
        if (mx < target) return target -mx;
        
        // 分组背包
        vector<vector<bool>> dp(m+1, vector<bool>(target+1, false));
        dp[0][0] = true;
        int large = INT_MAX;
        for (int g=0; g < m; g++) {
            int next_large = INT_MAX;
            for (int x=0; x<=target; x++){
                for (int j=0; j<n; j++) {
                    int y = mat[g][j];
                    if (dp[g][x] && x + y > target) next_large = min(next_large, x+y);
                    if (x >= y) dp[g+1][x] = dp[g+1][x] || dp[g][x-y];
                    if (large != INT_MAX) next_large = min(next_large, large + y);
                }
            }
            large = next_large;

        }        

        for (int i=target; i>=0; i--) if (dp[m][i]) return min(target-i, large-target);
        return large-target;
    }
};