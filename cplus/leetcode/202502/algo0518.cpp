#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  完全背包
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // 自行解答 完全背包 
        vector<unsigned> dp(amount+1, 0); // unsigned 不会溢出
        dp[0] = 1;
        for (auto& x : coins) 
            for (int k=x; k<=amount; k++) 
                dp[k] += dp[k-x];  

        return dp[amount];       
    }
};