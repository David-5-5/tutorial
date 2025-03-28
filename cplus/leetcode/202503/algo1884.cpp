#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int twoEggDrop(int n) {
        // 递归 -> 递推
        vector<int> dp(n+1, INT_MAX);
        dp[1] = 1;
        for (int i=2; i<=n; i++) {
            for (int j=1; j<i; j++) {
                dp[i] = min(dp[i], max(1+dp[i-j], j));
            }
        }
        return dp[n];

        // 数学 参考题解
        // return ceil((sqrt(n * 8 + 1) - 1) / 2)
    }
};