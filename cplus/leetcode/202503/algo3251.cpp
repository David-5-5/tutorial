#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  3250 的进阶版
class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        // 自行解答
        const int mod = 1e9 + 7;
        int n = nums.size(), mx = ranges::max(nums);

        vector<vector<int>> dp(n, vector<int>(mx+1));
        
        for (int j=0; j<=nums[0]; j++)  dp[0][j] = 1; // 初始值

        for (int i=1; i<n; i++) {
            for (int j=0; j<=nums[i]; j++) {
                int d = max(0, nums[i] - nums[i-1]);
                if (j+d > nums[i]) break;
                // 不需要显式计算前缀和
                // 完成方法或技巧，基于 countOfPairs3 方法 
                // 根据例子，单步跟踪，找出 j 和 n_s 的关系，总结出规律!!!
                dp[i][j+d] = ((j+d>0?dp[i][j+d-1]: 0)  + dp[i-1][j]) % mod;
            }

        };

        int ans = 0;
        for (auto v:dp[n-1]) ans = (ans + v) % mod;
        return ans;        
    }
};