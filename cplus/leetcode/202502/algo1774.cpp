#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  0-1 背包
class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int x = *min_element(baseCosts.begin(), baseCosts.end());
        if (x >= target) {
            return x;
        }
        
        // 超出 target 的取最小值，最接近target
        int res = 2 * target - x;

        // dp 为 1 的下标可以取得的值 下标<=target
        // 需要最接近 target 的值，因此最大值即可
        vector<int> dp(target + 1); 

        for (auto& base: baseCosts) {
            if (base <= target) dp[base] = true;  // base 必选，初始化即可
            else res = min(res, base);            // 超出 target 的取最小值
        }

        for (auto& w:toppingCosts) 
            for (int i=0; i<2; i++) // 每种配料最多用两次
                for (int k=target; k>=0; k--) {
                    if (dp[k] && k+w > target) res = min(res, k+w); // 一定要在前面
                    if (k >=w ) dp[k] |= dp[k-w];
                }
        
        for (int i = 0; i <= res - target; ++i) {
            if (dp[target - i]) {
                return target - i;
            }
        }
        return res;
        
    }
    
};