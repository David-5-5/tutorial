#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  0-1 背包
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // 参考题解
        // 按题意实际上将 stones 分为两组，要求两组的和相差最小
        // 因此可以转换为 0-1 背包，背包大小为 sum / 2
        // 区别于 2035 分两组，每组的数量一样，但其数值的大小10 ^ 7 
        // 使用背包会超时
        int sum = accumulate(stones.begin(), stones.end(), 0);

        vector<int> dp(sum/2 + 1);
        dp[0] = true;
        for (auto& w:stones) 
            for (int k=sum; k>=w; k--)
                dp[k] |= dp[k-w]
        
        for (int k=sum; k>=0; k--) 
            if (dp[k]) return sum - 2 * k;

        return -1; // 为 leetcode 编译要求
    }
};