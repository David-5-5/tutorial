#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列 (LIS)
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);  // 两个维度排序
        }); 

        vector<int> dp;

        for (auto& env : envelopes) {
            if (dp.size() == 0 || env[1] > dp.back()) dp.push_back(env[1]);
            else{
                int inx = ranges::lower_bound(dp, env[1]) - dp.begin();
                dp[inx] = env[1];
            }

        }
        return dp.size();
    }
};