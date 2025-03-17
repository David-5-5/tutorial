#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        // 参考题解 动态规划
        int n = obstacles.size();
        vector<int> dp = {1, 0, 1};     // 每条赛道的初始侧跳次数
        for (int i=1; i<n; i++) {
            int minCnt = INT_MAX;
            for (int j=0; j<3; j++) {                
                if (j==obstacles[i]-1) {
                    dp[j] = INT_MAX;
                } else {
                    minCnt = min(minCnt, dp[j]);
                }
            }
            for (int j = 0; j < 3; j++) {
                if (j == obstacles[i] - 1) {
                    continue;
                }
                dp[j] = min(dp[j], minCnt + 1); // minCnt + 1 从其他道跳入
            }

        }
        return *min_element(dp.begin(), dp.end());
    }
};