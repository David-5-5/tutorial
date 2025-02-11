#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  完全背包
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 自行解答 完全背包 
        // 关键在设置边界条件及赋值时机
        vector<int> dp(amount+1, -1);
        dp[0] = 0;
        for (auto& x : coins) {
            for (int k=x; k<=amount; k++) {
                if (dp[k-x] == -1) continue;    // dp[k-x] is invalid
                if (dp[k] == -1) dp[k] = dp[k-x] + 1; // initial dp[k]
                else dp[k] = min(dp[k], dp[k-x]+1);   // set the minimize
            }
        }

        return dp[amount];
        
    }
};