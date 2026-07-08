#include <bits/stdc++.h>
using namespace std;

// 六、状态机 DP - 6.3 进阶
class Solution {
public:
    int longestArithmetic(vector<int>& nums) {
        // 前后缀分解
        int n = nums.size();
        vector<int> suf(n, 1); suf[n-2] = 2;
        for (int i=n-3; i; i--) 
            if (2 * nums[i+1] == nums[i] + nums[i+2])
                suf[i] += suf[i+1];
            else suf[i] = 2;
        int ans = suf[1] + 1, pre = 1;
        for (int i=1; i<n-1; i++) {
            ans = max(ans, max(pre+1, suf[i+1]+1));
            if (i>=2 && i<=n-3) {
                if (nums[i-1]-nums[i-2] == nums[i+2] - nums[i+1] && 2 * (nums[i+2] - nums[i+1]) == nums[i+1] - nums[i-1])
                    ans = max(ans, pre + suf[i+1] + 1);
            }
            if (i<=n-3 && nums[i+1] - nums[i-1] == 2 * (nums[i+2] - nums[i+1])) ans = max(ans, suf[i+1] + 2);
            if (i>=2 && 2 * (nums[i-1] - nums[i-2]) == nums[i+1] - nums[i-1]) ans = max(ans, pre + 2);
            
            if (i>=2 && nums[i-1] - nums[i-2] == nums[i]-nums[i-1]) pre += 1;
            else pre = 2;
        }
        
        return max(ans, pre + 1);
    }

    int longestArithmetic(vector<int>& nums) {
        // 状态机 DP
        int n = nums.size();
        vector dp(n, vector<int>(2));
        dp[0][0] = 1, dp[0][1] = 1; dp[1][0] = 2, dp[1][1] = 2;
        for (int i=2; i<n; i++) {
            for (int left = 0; left<2; left ++){
                // 不改
                auto & res = dp[i][left] = 2;
                if (nums[i-2] + nums[i] == 2 * nums[i-1]) {
                    res = dp[i-1][left] + 1;
                }
                if (left) {
                    res = max(res, 3);  // 改 nums[i-2]
                    if (i >= 3) {
                        if ((nums[i-2] - nums[i-3]) * 2 == nums[i]-nums[i-2])
                            res = max(res, dp[i-2][0] + 2); // 改 nums[i-1]
                        
                        // 改 nums[i-2]
                        int d = nums[i] - nums[i-1];
                        if (nums[i-1] - nums[i-3] == d * 2) {
                            res = max(res, 4);
                            if (i >= 4 && nums[i-3] - nums[i-4] == d) 
                                res = max(res, dp[i-3][0] + 3);
                        }
                    }
                }
            }
        }

        int ans1 = 0, ans2 = 0;
        for (int i=0; i<n; i++) {
            ans1 = max(ans1, dp[i][1]);
            if (i<n-1) ans2 = max(ans2, dp[i][0] + 1);
        }
        return max(ans1, ans2);
    }    
};