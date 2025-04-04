#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 一维 DP
class Solution {
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        // 参考题解
        vector<int> minSec(17, INT_MAX / 2);

        for (auto& x : tires) {
            int sec = x[0];
            // 第 i 圈的用时不应超过 sec<=changeTime+x[0]，否则更换轮胎即可
            for (int i=1, sum=0; sec<=changeTime+tire[0]; i++) {
                sum += sec;
                minSec[i] = min(sec, minSec[i]);
                sec *= x[1];
            }
        }

        vector<int> dp(numLaps+1, INT_MAX);
        dp[0] = -changeTime;
        for (int i=1; i<=numLaps; i++) {
            for (int j=1; j<min(17, i); j++)
                dp[i] = min(dp[i], dp[i-j] + minSec[j]);  // 连续跑 j 圈转移方程
            dp[i] += changeTime;    // 更换轮胎时间
        }

        return dp[numLaps];

    }
};