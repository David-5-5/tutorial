#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    int jewelleryValue(vector<vector<int>>& frame) {
        // 自行解答 动态规划
        int n = frame.size(), m = frame[0].size();
        vector dp(n, vector<int>(m, 0));
        dp[0][0] = frame[0][0];
        for (int i=0; i<n; i++) for (int j=0; j<m; j++) {
            if (i) dp[i][j] = max(dp[i][j], frame[i][j] + dp[i-1][j]);
            if (j) dp[i][j] = max(dp[i][j], frame[i][j] + dp[i][j-1]);
        }
        return dp[n-1][m-1];
    }
};