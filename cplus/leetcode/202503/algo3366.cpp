#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int ans = accumulate(nums.begin(), nums.end(), 0), n = nums.size();

        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(op1+1, vector<int>(op2+1, INT_MAX)));
        dp[0][op1][op2] = ans;
        
        for (int i=0; i<n; i++) {
            for (int p=0; p<=op1; p++) {
                for (int q=0; q<=op2; q++) {

                    dp[i+1][p][q] = min(dp[i+1][p][q], dp[i][p][q]); // 不操作
                    if (p>0) dp[i+1][p-1][q] = min(dp[i+1][p-1][q], dp[i][p][q] - nums[i]/ 2);
                    if (q>0 && nums[i]>=k) dp[i+1][p][q-1] = min(dp[i+1][p][q-1], dp[i][p][q] - k);
                    if (p>0 && q>0 && nums[i]>k) {  // 同时进行两种操作
                        // 检测先除后减， 存在 执行操作1后不满足执行操作2的条件
                        int val1 = (nums[i] >= k+nums[i]/2)? dp[i][p][q] - nums[i]/ 2 - k: INT_MAX;
                        int val2 = dp[i][p][q] - k - (nums[i] - k)/2;
                        dp[i+1][p-1][q-1] = min(dp[i+1][p-1][q-1], min(val1, val2));
                    }
                }
            }
        }
        
        for (int p=0; p<=op1; p++) {
            for (int q =0; q<=op2; q++) {
                ans = min(ans, dp[n][p][q]);
            }
        }
        return ans; 

    }
};