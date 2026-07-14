#include <bits/stdc++.h>
using namespace std;


// 同 codeforces 1575L
class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        // 同 354 偏序
        auto longestPairChain = [&](vector<vector<int>>& pairArr) -> int {
            if (pairArr.size() == 0) return 0;
            sort(pairArr.begin(), pairArr.end(), [](const auto& e1, const auto& e2) {
                return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);  // 两个维度排序
            });

            vector<int> dp;

            for (auto& env : pairArr) {
                // 第二维 大于等于
                // if (dp.size() == 0 || env[1] >= dp.back()) dp.push_back(env[1]);
                // else{
                //     int inx = ranges::upper_bound(dp, env[1]) - dp.begin();
                //     dp[inx] = min(env[1], dp[inx]);
                // }
                auto it = ranges::upper_bound(dp, env[1]);
                if (it == dp.end()) dp.push_back(env[1]);
                else *it = env[1];

            }
            return dp.size();
        };

        vector<vector<int>> ans;
        int n = nums.size();
        for (int i=0; i<n; i++) {
            auto & v = nums[i];
            if (v <= i) {
                ans.push_back({v, i-v});
            }
        }

        return longestPairChain(ans);
    }
};