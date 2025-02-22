#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        // 参考题解 O(n^2) 解法  按照(分数,年龄)排序
        int n = scores.size();
        vector<vector<int>> zip;
        for (int i=0; i<n; i++)
            zip.push_back({scores[i], ages[i]});
        
        sort(zip.begin(), zip.end());

        int ans = 0;
        vector<int> dp(n, 0);

        for (int i=0; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (zip[i][1] >= zip[j][1]) dp[i] = max(dp[i], dp[j]);
            }
            dp[i] += zip[i][0];
            ans = max(ans, dp[i]);
        }
        return ans;
    }


};