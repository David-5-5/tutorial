#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        // 参考题解
        int n = cost.size(), m = cost[0].size(), st = 1 << m;
        
        int n = cost.size(), m = cost[0].size(), st = 1 << m;
        
        vector<vector<int>> dp(n+1,vector<int>(st, INT_MAX/2));
        dp[0][0] = 0;
        for (int i=1; i<=n; ++i) for (int s=1; s<st; ++s) {
            for (int k=0; k<m; ++k) {
                if (s>>k & 1) {
                    dp[i][s] = min(dp[i][s], min(dp[i][s^1<<k], 
                            min(dp[i-1][s], dp[i-1][s^1<<k])) + cost[i-1][k]);
                }
            }
            
        }
        return dp[n][st-1];
    }


};