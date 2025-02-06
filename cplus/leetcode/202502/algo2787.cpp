#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 0-1 背包
class Solution {
public:
    int numberOfWays(int n, int x) {
        // 自行解答 标准 0-1 背包
        int mod = 1e9+7;
        vector<int> dp(n+1);
        dp[0] = 1;

        for (int i=1; i<=300; i++) {
            int y = int(pow(i, x));
            if (y>n) break;
            for(int j=n; j>=y; j--){
                dp[j] = (dp[j] + dp[j-y]) % mod;
            }
        }

        // int mx = ceil(pow(n, 1.0/x));
        // for (int i=1; i<=mx; i++) {
        //     int y = int(pow(i, x));
        //     for(int j=n; j>=y; j--){
        //         dp[j] = (dp[j] + dp[j-y]) % mod;
        //     }
        // }

        return dp.back();        
    }
};