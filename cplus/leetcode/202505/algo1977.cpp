#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.1 前缀和优化 DP 难度分：2817
class Solution {
public:
    int numberOfCombinations(string num) {
        // 自行解答 记忆化搜索 -> 递推 见 python
        // 直接从 python 转换过来，memory overtime
        if (num[0] == '0') return 0;

        const int mod = 1e9 + 7, n = num.size();
        vector<vector<int>> dp(n+1, vector<int>(n));
        
        for (int j=0; j<n; ++j) dp[n][j] = 1;
        for (int i=n-1; i>=0; --i) {
            if (num[i] == '0') {
                for (int j=0; j<n; ++j) dp[i][j] = 0;
                continue;
            }
            int sum = 0;
            for (int k=i+1; k<=n-i; ++k) sum += dp[i+k][i];

            for (int j=max(0, 2*i-n); j<=i; ++j) {
                if (num.substr(i, i-j) >= num.substr(j,i-j))
                    sum = ((long)dp[i+i-j][i] + sum) % mod;
                dp[i][j] = ((long)dp[i][j] + sum) % mod;
                if (num.substr(i, i-j) < num.substr(j,i-j))
                    sum = ((long)dp[i+i-j][i] + sum) % mod;

            }
        }

        return dp[0][0];
    }
};