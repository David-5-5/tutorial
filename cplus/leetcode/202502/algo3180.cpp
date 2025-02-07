#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 0-1 背包
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        // 自行解答  c++ 的实现，性能比 python 都慢
        sort(rewardValues.begin(), rewardValues.end());
        set<int> rewards;

        for (auto& v: rewardValues) {
            set<int> cur;
            cur.emplace(v); // set 自动从小到大排序
            for (auto& u : rewards) {
                if (u >= v) break;
                cur.emplace(u+v);
            }
            rewards.merge(cur);
        }
        
        return *max_element(rewards.begin(), rewards.end()); 
    }


    int maxTotalReward(vector<int>& rewardValues) {
        // 参考题解 0-1 背包 需要一些技巧才能应用上 0-1 背包
        sort(rewardValues.begin(), rewardValues.end()); // 从小到大遍历数组
        int m = rewardValues.back();
        // 由于 rewordValue[i] 大于当前总奖励数和，总奖励数最大为  2 * max(rewardValues)
        vector<int> dp(m * 2);

        dp[0] = 1;
        for (auto v: rewardValues)  
            for (int k=v*2-1; k>=v; k--)  // 当前 v 最多仅加上 v-1
                if (dp[k] == 0) dp[k] = dp[k-v];

        for (int i=m*2-1; i>=0; i--)
            if (dp[i]) return i;

        return -1;  // 仅为编译通过
    }
};