#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  0-1 背包
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        // 2023,2024 用 dp 的题目
        // 用 2-d 0-1 背包超时
        int height = accumulate(rods.begin(), rods.end(), 0) / 2;

        vector<vector<bool>> dp(height+1, vector<bool>(height+1));
        dp[0][0] = true;
        for (auto& r: rods)
            for (int i=height; i>=0; i--) 
                for (int j=height; j>=0; j--) {
                    if (i >= r) dp[i][j] = dp[i][j] | dp[i-r][j];
                    if (j >= r) dp[i][j] = dp[i][j] | dp[i][j-r];
                }
        for (int k=height; k>0; k--) 
            if (dp[k][k]) return k;
        
        return 0;
        
    }
};