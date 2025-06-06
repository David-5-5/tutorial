#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 14. 博弈 DP
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        // 自行解答，记忆化开始 递归 -> 递推 -> 优化 参见 python
        int n = stones.size();
        vector<int> pres(n+1);
        for (int i=0; i<n; ++i) pres[i+1] = pres[i] + stones[i];
        
        vector<int> dp(n);
        dp[n-1] = pres[n];
        for (int i=n-2; i; --i) {
            dp[i] = max(dp[i+1], pres[i+1]-dp[i+1]);
        }
        return dp[1];
    }
};