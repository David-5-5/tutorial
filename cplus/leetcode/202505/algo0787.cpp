#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 13. 图 DP
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // 二维 DP
        vector<vector<int>> dp(k+2, vector<int>(n, INT_MAX/2));
        dp[0][src] = 0;
        for (int t=1; t<=k+1; t++) {
            for (auto& f: flights) {
                int i = f[0], j = f[1], c = f[2];
                dp[t][j] = min(dp[t][j], dp[t-1][i] + c);
            }
        }

        int ans = INT_MAX/2;
        for (int t=1; t<=k+1; ++t) ans = min(ans, dp[t][dst]);
        return ans<INT_MAX/2? ans: -1;
        
    }

    int findCheapestPrice2(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // 二维 DP - 优化 - 空间一维
        vector<int> dp(n, INT_MAX/2);
        dp[src] = 0;
        int ans = INT_MAX/2;
        for (int t=1; t<=k+1; t++) {
            vector<int> g(n, INT_MAX/2);
            for (auto& f: flights) {
                int i = f[0], j = f[1], c = f[2];
                g[j] = min(g[j], dp[i] + c);
            }
            dp = move(g);
            ans = min(ans, dp[dst]);
        }


        return ans<INT_MAX/2? ans: -1;
        
    }    
};