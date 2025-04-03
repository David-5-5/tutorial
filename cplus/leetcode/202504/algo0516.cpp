#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  区间 DP
// 复习
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        // 复习，模板 - 最长回文子序列
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i=n-1; i>=0; i--) {
            dp[i][i] = 1;
            for (int j=i+1; j<n; j++) {
                if (s[i] == s[j]) dp[i][j] = 2 + dp[i+1][j-1];
                else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
        return dp[0][n-1];

    }
};