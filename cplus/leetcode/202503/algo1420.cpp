#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        // 自行解答
        const int mod = 1e9 + 7;

        vector<vector<vector<int>>> memo(n, vector<vector<int>>(m+1, vector<int>(k+1, -1)));
        auto dfs = [&](this auto&& dfs, int i, int j, int l) -> int {
            if (l<0) return 0;
            if (i == n) return l==0?1:0;

            auto& res = memo[i][j][l];

            if (res != -1) return res;

            res = 0;
            for (int v=1; v<=m; v++) {
                res = (res + dfs(i+1, max(j, v), l-(j<v))) % mod;
            }

            return res;
        };
        
        return dfs(0, 0, k);

    }

    int numOfArrays2(int n, int m, int k) {
        // 递归 -> 递推
        const int mod = 1e9 + 7;

        int dp[n][m+1][k+1];
        memset(dp, 0, sizeof(dp));

        for (int j=1; j<=m; j++) {
            dp[0][j][1] = 1;        // 第 0 个 值为 j 使用 cost 计数 1
        }
        
        for (int i=1; i<n; i++) {
            for (int l = 1; l<=k && l<=i+1; l++) {
                for (int j=1; j<=m; j++) {
                    dp[i][j][l] = (long) dp[i-1][j][l] * j % mod;    // j 为最大值
                    for (int j0=1; j0 < j; j0++) {            // j0 is prevoius
                        dp[i][j][l] = (dp[i][j][l] + dp[i-1][j0][l-1]) % mod;
                    }
                }
            }
        }

        int ans = 0;
        for (int j=1; j<=m; j++)
            ans = (ans + dp[n-1][j][k]) % mod;

        return ans;
    }


};