#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        // 由递归(python) -> 递推
        int n = nums.size();

        vector<int> pres(n+1, 0);
        for (int i=0; i<n; i++) pres[i+1] = pres[i] + nums[i];
        

        vector<vector<int>> intv_mx(n, vector<int>(n, -1));
        for (int i=0; i<n; i++) 
            for (int j=i; j<n; j++)
                if (i == j) intv_mx[i][j] = nums[j];
                else intv_mx[i][j]= max(intv_mx[i][j-1], nums[j]);

        // 边界条件 初始化都为 INT_MAX/2 (INT_MAX 加法越界)
        vector<vector<int>> dp(n, vector<int>(k+2, INT_MAX/2));
        for (int r=0; r<n; r++) {
            for (int j=1; j<=k+1; j++) {
                for (int l=0; l<=r; l++) {
                    // 关键 dp[l-1][j-1] 进行状态转移 不是 dp[r-1][j-1]
                    dp[r][j] = min(dp[r][j], (l==0?0:dp[l-1][j-1]) + intv_mx[l][r]*(r-l+1) - (pres[r+1]-pres[l]));
                }
            }
        }

        return dp[n-1][k+1];
    }
};