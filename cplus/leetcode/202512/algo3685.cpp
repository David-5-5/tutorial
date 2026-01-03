#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 三、背包 3.1 0-1 背包 进阶
class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        // 参考题解，0-1背包的灵活运用
        int n = nums.size(); vector<bool> ans(n);
        vector<bool> dp(1 + k);  dp[0] = true;
        sort(nums.begin(), nums.end());
        
        int i = 0;
        for (int x=1; x<=n; ++x) {
            while (i < n && nums[i] == x) {
                for (int j=k; j>=x; j--) {
                    dp[j] = dp[j] || dp[j-x];
                }
                i++;
            }
            for (int j=0; j<=min(n-i, k/x); j++) {
                if (dp[k-j*x]) {
                    ans[x-1] = true; break;
                }
            }
        }
        return ans;
    }
};