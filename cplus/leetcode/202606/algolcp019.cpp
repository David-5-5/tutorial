#include <bits/stdc++.h>
using namespace std;

// 六、状态机 DP - 6.3 进阶
class Solution {
public:
    int minimumOperations(string leaves) {
        // state: 0 1 2
        // 0: 0~i red, 1: x~i yellow, 2: x~i red
        // state 0 -> 1 -> 2
        // dp[0][0] = isYellow
        // dp[0][1] = dp[0][2] = dp[1][2] = INT_MAX invalid state
        int n = leaves.length();
        vector dp(n, vector<int>(3));
        dp[0][0] = (leaves[0] ==  'y');
        dp[0][1] = dp[0][1] = dp[1][2] = INT_MAX;
        for (int i=1; i<n; i++) {
            dp[i][0] = dp[i-1][0] + (leaves[i] ==  'y');
            dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + (leaves[i] ==  'r');
            if (i>1) {
                dp[i][2] = min(dp[i-1][2], dp[i-1][1]) + + (leaves[i] ==  'y');
            }
        }

        return dp[n-1][2];
    }
}; 