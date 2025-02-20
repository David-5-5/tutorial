#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最长递增子序列（LIS）
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        vector<int> dp, ans;

        for (auto& x : obstacles) {
            auto it = ranges::upper_bound(dp, x);
            if (it != dp.end()) {
                *it = x;
                ans.push_back(it - dp.begin() + 1);
            }
            else {
                dp.push_back(x);
                ans.push_back(dp.size());
            }
        }
        return ans;
    }
};