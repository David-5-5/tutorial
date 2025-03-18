#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int numWays(int steps, int arrLen) {
        // 自行解答
        const int mod = 1e9 + 7;
        int right = min(steps/2+1, arrLen); // 向左最大不能超过 steps / 2 + 1

        vector<vector<int>> memo(steps+1, vector<int>(right, -1));

        auto dfs = [&](this auto&& dfs, int i, int j) {
            if (i==0) return j==0?1:0;

            auto& res = memo[i][j];
            if (res != -1) return res;
            // 分别对应停留远地点，向左，向右
            return res = ((long)dfs(i-1, j) + (j>0?dfs(i-1,j-1):0) + (j+1<right?dfs(i-1,j+1):0))%mod;
        };

        return dfs(steps, 0);
    }

    int numWays2(int steps, int arrLen) {
        // 记忆化搜索 -> 递推
        const int mod = 1e9 + 7;
        int right = min(steps/2+1, arrLen); // 向左最大不能超过 steps / 2 + 1

        vector<vector<int>> dp(steps+1, vector<int>(right, 0));
        dp[0][0] = 1;

        for (int i=0; i<steps; i++) {
            for (int j=0; j<right; j++) {
                dp[i+1][j] = ((long)dp[i][j] + (j>0?dp[i][j-1]:0) + (j+1<right?dp[i][j+1]:0)) % mod;
            }
        }
        
        return dp[steps][0];
    }
}; 