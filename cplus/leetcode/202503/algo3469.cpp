#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minCost(vector<int>& nums) {
        // 由递归改递推，递归实现参见 python
        // 参考题解，比较抽象，不太容易理解边界条件
        int n = nums.size();

        vector<vector<int>> dp(n+1, vector<int>(n));

        dp[n] = nums;
        for (int i=0; i<n; i++) 
            dp[n-1][i] = max(nums[i], nums[n-1]);

        for (int i=n-3 + n%2; i>0; i-=2) {
            int b = nums[i], c = nums[i+1];
            for (int j=0; j<i; j++) {
                int a = nums[j];
                dp[i][j] = min({dp[i+2][j] + max(b,c), 
                                dp[i+2][i] + max(a,c),
                                dp[i+2][i+1] + max(a, b)});
            }

        }
        return dp[1][0];
    }
};