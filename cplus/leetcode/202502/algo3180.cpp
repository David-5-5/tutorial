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
};