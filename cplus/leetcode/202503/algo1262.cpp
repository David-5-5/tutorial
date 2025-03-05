#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 进阶
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        // 自行解答
        int n = nums.size();

        vector<int> dp(3, -1);  // -1 表示未初始化，不存在有效值
        vector<int> newdp(3, -1);
        dp[0] = 0;

        for (int i=0; i<n; i++) {
            for (int j=0; j<3; j++) {
                if (dp[j] != -1) newdp[j] = dp[j] + nums[i];
            }
            for (int j=0; j<3; j++) {
                if (newdp[j] != -1) {       // 新的值重新 % 3, 
                    int x = newdp[j]%3;
                    dp[x] = max(dp[x], newdp[j]);
                }
            }
        }

        return dp[0];      
    }
};