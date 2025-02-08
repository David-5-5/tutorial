#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  0-1 背包
class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        // 参考题解 : 本题比较困难的部分包括：
        // 1. baseCosts 必选，即设置为初始条件
        // 2. 超过 toppingCosts 的最小值，有技巧，详见涉及的代码行
        int x = *min_element(baseCosts.begin(), baseCosts.end());
        if (x >= target) {
            return x;
        }
        
        // 超出 target 的取最小值，最接近target
        int res = 2 * target - x; // 由于 x 是最小base，因此这是最大值

        // dp 为 1 的下标可以取得的值 下标<=target
        // 需要最接近 target 的值，因此最大值即可
        vector<int> dp(target + 1); 

        for (auto& base: baseCosts) {
            if (base <= target) dp[base] = true;  // base 必选，初始化即可
            else res = min(res, base);            // 按照 base 取最小值
        }

        for (auto& w:toppingCosts) 
            for (int i=0; i<2; i++) // 每种配料最多用两次
                for (int k=target; k>=0; k--) {
                    // 超出部分取最小值，一定要在前面， 放在下一行，相当于一次增加了 2 个 w
                    if (dp[k] && k+w > target) res = min(res, k+w); 
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