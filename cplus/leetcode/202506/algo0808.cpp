#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 15. 概率/期望 DP
class Solution {
public:
    double soupServings(int n) {
        // 记忆化搜索见python，递归->迭代
        if (n > 180 * 25) return 1;
        n = n/25 + (n%25 != 0);

        vector dp(n+1, vector<double>(n+1));
        dp[0][0] = 0.5;     // a==0, b==0
        for (int a=1; a<=n; a++) dp[a][0] = 0;
        for (int b=1; b<=n; ++b) dp[0][b] = 1;

        for (int a=1; a<=n; ++a) for(int b=1;b<=n;++b) {
            dp[a][b] = dp[max(0,a-4)][b-0] + dp[max(0,a-3)][max(0, b-1)] + 
                        dp[max(0,a-2)][max(0, b-2)] + dp[max(0,a-1)][max(0, b-3)];
            dp[a][b] /= 4;
        }

        return dp[n][n];
    }   
};