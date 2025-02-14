#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  完全背包
class Solution {
public:
    int numSquares(int n) {
        vector<int> squares;
        for (int i=1; i<=sqrt(n); i++) {
            squares.push_back(i*i);
        }

        vector<int> dp(n+1, -1);
        dp[0] = 0;
        for (auto& x : squares) {
            for (int k=x; k<=n; k++) {
                if (dp[k-x] == -1) continue;          // dp[k-x] is invalid
                if (dp[k] == -1) dp[k] = dp[k-x] + 1; // initial dp[k]
                else dp[k] = min(dp[k], dp[k-x]+1);   // set the minimize
            }
        }

        return dp[n];
    }
};