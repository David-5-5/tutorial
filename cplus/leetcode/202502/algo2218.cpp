#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  分组背包
class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        // 参考题解 f[i]←f[i−t]+ ∑ piles[j][p], j in [0,t-1] 
        // 转化为背包，每行选择的列数 1~piles[i].size() 为空间，sum(piles[i]) 为价值
        
        int m = piles.size();
        
        vector<int> dp(k+1, -1);
        dp[0] = 0; 
        for (int g=0; g<m; g++) {
            for (int x=k; x>=0; x--) {
                int value = 0;
                for (int t=1; t<=piles[g].size(); t++) {
                    value += piles[g][t-1]; // 从 1 开始枚举，累计前缀和
                    if (x>=t && dp[x-t]!=-1) dp[x] = max(dp[x], dp[x-t] + value);
                }
            }
        }

        return dp[k];

    }
};