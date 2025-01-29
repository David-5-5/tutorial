#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 爬楼梯
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // 自行解答
        cost.push_back(0);
        vector<int> dp(cost.size());
        dp[0] = cost[0], dp[1] = cost[1];

        for (int i=2; i<cost.size(); i++) 
            dp[i] = min(dp[i-1], dp[i-2]) + cost[i];
        
        return dp[cost.size()-1];
    }

    int minCostClimbingStairs(vector<int>& cost) {
        // 参考题解
        vector<int> dp(cost.size()+1);

        for (int i=2; i<=cost.size(); i++) 
            dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]);
        
        return dp[cost.size()];
    }
};