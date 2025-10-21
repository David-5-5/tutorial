#include <bits/stdc++.h>
using namespace std;


// 数学算法 - 组合数学 - 2.3 放球问题
class Solution {
public:
    int numberOfSets(int n, int k) {
        // 动态规划 python 记忆化搜索 -> 递推 -> 前缀和优化
        const int mod = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(k+1));
        dp[0][0] = 1;
        vector<long long> pres(k);

        for (int i=1; i<n; ++i) {
            dp[i][0] = 1;
            for (int j=1; j<=k; ++j) {
                if (i < j) continue;
                dp[i][j] = dp[i-1][j];
                pres[j-1] += dp[i-1][j-1];
                // max_k 是 i-j-1，即剩余的点至少包含 j-1 个段
                if (j-2>=0) pres[j-1] -= dp[j-2][j-1];
                dp[i][j] = (dp[i][j] + pres[j-1]) % mod;
            }
        }
        return dp[n-1][k];
    }
};