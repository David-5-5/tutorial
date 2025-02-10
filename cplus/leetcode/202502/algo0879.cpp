#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  0-1 背包
class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        // 二维背包 工人 和 利润
        // 参考题解 关键点 至少为 minProfit, 不需要计算大于 minProfit 的写法 详见代码
        int mod = 1e9 + 7;
        vector<vector<int>> dp(n+1, vector<int>(minProfit+1)); // 0 的数量
        dp[0][0] = 1;

        for (int k=0; k<group.size(); k++) {
            int emp = group[k], pro = profit[k];

            for (int i=n; i>=emp; i--) 
                for (int j=minProfit; j>=0; j--) // 关键点1 ：使用 j>=0 代替 j>=pro
                    // 关键点2 使用 max(0,j-pro) 代替 j-pro
                    dp[i][j] = (dp[i][j]+dp[i-emp][max(0,j-pro)]) % mod; 
            
        }

        int ans = 0;
        for (int i=0; i<=n; i++) ans = (ans + dp[i][minProfit]) % mod;
        return ans;
    }
};