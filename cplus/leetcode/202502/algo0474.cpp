#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  0-1 背包
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        // 学习 OI-wiki 二维背包
        vector<vector<int>> dp(m+1, vector<int>(n+1)); // 0 的数量

        for (auto& s: strs) {
            int cnt0 = 0, cnt1 = 0;
            for (auto& ch: s) {
                if (ch == '0') cnt0 ++;
                else cnt1 ++;
            }

            for (int i=m; i>=cnt0; i--) 
                for (int j=n; j>=cnt1; j--)
                    dp[i][j] = max(dp[i][j], dp[i-cnt0][j-cnt1]+1);
            
        }

        return dp[m][n];
    }
};