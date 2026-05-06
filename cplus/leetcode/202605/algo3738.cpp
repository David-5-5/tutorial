#include <bits/stdc++.h>
using namespace std;

// 六、状态机 DP - 6.3 进阶
class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        // 参考题解 状态 DP
        int n = nums.size(), ans = 1;
        if (n <= 2) return n;

        vector dp(n, vector<int>(2, 1));
        
        for (int i = 1; i<n; i++) {
            if (nums[i] >= nums[i-1]) {
                dp[i][0] += dp[i-1][0]; dp[i][1] += dp[i-1][1];
            }
            // 将 nums[i-1] == nums[i-2]
            if (i>=2 && nums[i] >= nums[i-2]) dp[i][1] = max(dp[i][1], dp[i-2][0]+2);
            else dp[i][1] = max(dp[i][1], 2);   // 将前面改小

            // dp[i][1] 都仅保存将前面的值减少的得到最长子序列
            // 这样 nums[i] 值不需要改变，不影响数组元素大小的判读，精妙!!!
            ans =  max(ans, max(dp[i-1][0] + 1, dp[i][1])); // 将自身增加
        }

        return ans;
        
    }
};