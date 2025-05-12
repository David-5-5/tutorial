#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.7 斜率优化 DP
class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        // 自行解答 规律是发现了, 不够代码不好写, 时间复杂度
        int n = skill.size(), m = mana.size();

        // 先不减少纬度
        vector<vector<long long>> dp(m+1, vector<long long>(n+1));
        for (int i=1; i<=m; ++i) {
            for (int j=1; j<=n; ++j) {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + skill[j-1] * mana[i-1];
            }
            for (int j=n; j; --j) {
                dp[i][j-1] = dp[i][j] - skill[j-1] * mana[i-1];
            }
        }
        return dp[m][n];

    }


    long long minTime(vector<int>& skill, vector<int>& mana) {
        // 参考题解, 空间复杂度降低一维
        int n = skill.size(), m = mana.size();

        // 先不减少纬度
        vector<long long> dp(n+1);
        for (int i=1; i<=m; ++i) {
            for (int j=1; j<=n; ++j) {
                dp[j] = max(dp[j], dp[j-1]) + skill[j-1] * mana[i-1];
            }
            for (int j=n; j; --j) {
                dp[j-1] = dp[j] - skill[j-1] * mana[i-1];
            }
        }
        return dp[n];

    }
    
};