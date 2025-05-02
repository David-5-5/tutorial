#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        // 参考题解
        int n = cost.size(), m = cost[0].size(), st = 1 << m;
        
        // i 表示cost1 的序号 s 表示 cost2 的状态压缩
        // dfs(i, s) 表示 cost1 的前 i 个元素和 cost2 的状态压缩 s
        // 其状态转移方程为
        // dfs(i, s) = min (dfs(i, s^1<<k), dfs(i-1, s), dfs(i-1, s^1<<k)) + cost[i-1][k] k in s
        // 当第 1 组的 i-1 个点与第 2 组的 k 点相连
        // 其中 dfs(i, s^1<<k) 表示 s 中的第 k 个点不与其他节点相连
        //      dfs(i-1, s) 表示 i-1 个节点不与第 2 组中的其他节点相连
        //      dfs(i-1, s^1<<k) 表示 i-1 个节点不与第 2 组中的其他节点相连
        //                       且 s 中的第 k 个点不与其他节点相连
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