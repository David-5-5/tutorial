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

    int numOfArrays3(int n, int m, int k) {
        // 前缀和优化
        const int mod = 1e9 + 7;

        int dp[n][m+1][k+1];
        memset(dp, 0, sizeof(dp));

        for (int j=1; j<=m; j++) {
            dp[0][j][1] = 1;        // 第 0 个 值为 j 使用 cost 计数 1
        }
        
        for (int i=1; i<n; i++) {
            for (int l = 1; l<=k && l<=i+1; l++) {
                int pres = 0;       // 前缀和
                for (int j=1; j<=m; j++) {
                    // 如果第 i 个数没有改变搜索代价，那么说明它不严格大于数组中的前 i−1 个数。
                    // 也就是说， dp[i][j][s] 会从 dp[i−1][j][s] 转移而来，
                    // 即数组中的前 i−1 个数的最大值已经是 j 了，第 i 个数没有改变最大值。
                    // 在这种情况下，第 i 个数可以在 [1,j] 的范围中任意选择，即：
                    // dp[i][s][j] = dp[i−1][s][j]∗j
                    
                    // 对应于 递归中的 max(j, v)
                    dp[i][j][l] = (long) dp[i-1][j][l] * j % mod;    // j 为最大值
                    dp[i][j][l] = ((long)dp[i][j][l] + pres) % mod;

                    pres = ((long) pres + dp[i-1][j][l-1]) % mod;   // 前缀和加上当前
                }
            }
        }

        int ans = 0;
        for (int j=1; j<=m; j++)
            ans = (ans + dp[n-1][j][k]) % mod;

        return ans;
    }
};