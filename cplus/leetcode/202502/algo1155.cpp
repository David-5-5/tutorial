#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 多重背包
class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        // 学习 oi-wiki 分组背包 模板
        int mod = 1e9 + 7;
        vector<int> dp(target+1, 0);
        dp[0] = 1;
        for (int g=0; g<n; g++)             // 循环每一组, n个硬币
            for (int x=target; x>=0; x--) {  // 循环背包容量
                dp[x] = 0;                   // oi-wiki 模板求最大值，计数需要设置为 0
                for (int j=1; j<=k; j++)    // 每个硬币 k 个面
                    if (x>=j)
                        dp[x] = (dp[x] + dp[x-j]) % mod;
            }
        
        return dp[target];  
    }
};