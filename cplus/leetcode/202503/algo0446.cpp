#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  合法子序列 DP
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        // 参考题解
        int ans = 0, n = nums.size();

        vector<unordered_map<long long, int>> dp(n);
        for (int i=0; i<n; i++) {
            for (int j=0; j<i; j++) {
                long d = (long) nums[i] - nums[j];
                // int cnt = dp[j][d];
                // 另一种写法，性能优于上面的写法
                auto it = dp[j].find(d);
                int cnt = it == dp[j].end() ? 0 : it->second;
                
                ans += cnt;
                dp[i][d] += cnt + 1;
            }
        }
        return ans;
    }
};