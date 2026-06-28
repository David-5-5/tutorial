#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int waysToChange(int n) {
        // 完全背包
        const int mod = 1e9 + 7;
        vector<int> dp(n+1), coins = {1, 5, 10, 25};
        dp[0] = 1;
        for (auto coin: coins) for (int w=coin; w<=n; w++) {
            dp[w] = (dp[w] + dp[w-coin]) % mod;
        }

        return dp[n];
    }
};