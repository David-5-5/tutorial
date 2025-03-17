#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> dp = {1, 0, 1};
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
                dp[j] = min(dp[j], minCnt + 1);
            }

        }
        return *min_element(dp.begin(), dp.end());
    }
};