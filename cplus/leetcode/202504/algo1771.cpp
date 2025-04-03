#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  区间 DP
class Solution {
    public:
        int longestPalindrome(string word1, string word2) {
            // 516 最长回文子序列 变形题
            string s = word1 + word2;
            int n = s.length(), ans;
            vector<vector<int>> dp(n, vector<int>(n));
    
            for (int i=n-1; i>=0; i--) {
                dp[i][i] = 1;
                for (int j=i+1; j<n; j++) {
                    if (s[i] == s[j]) {
                        dp[i][j] = 2 + dp[i+1][j-1];
                        // 区别于 516 的地方，在符合要求的时机更新答案
                        if (i < word1.length() && j >= word1.length())
                            ans = max(ans, dp[i][j]);
                        // end ------------------------------
                    }
                    else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
            return ans;
        }
    };