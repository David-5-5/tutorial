#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        // 参考题解，难点 状态定义
        int n = nums.size(); int mx = 1, mn = 300;
        for (auto & v: nums) {
            mx = max(mx, v); mn = min(v, mn);
        }
        int max_d = mx - mn;

        // 表示以 nums[i] 结尾的、最后两个数之差至少为 j 的子序列的最长长度。
        vector dp(n, vector<int>(max_d + 2));
        vector<int> last(mx + 1, -1);

        int ans = 0;
        for (int i=0; i<n; i++) {
            auto x = nums[i];
            for (int j=max_d; j>=0; j--) {
                dp[i][j] = max(1, dp[i][j+1]);
                if (x - j >=0 && last[x-j] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[last[x-j]][j] + 1);
                }
                if (x + j <=mx && last[x+j] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[last[x+j]][j] + 1);
                }
                ans = max(ans, dp[i][j]);
            }
            last[x] = i;
        }
        return ans;
    }
};