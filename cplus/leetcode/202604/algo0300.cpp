#include <bits/stdc++.h>
using namespace std;

// 四、经典线性 DP 4.2 最长递增子序列（LIS） 4.2.1 基础
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> ans;
        for (auto& v: nums) {
            int idx = ranges::lower_bound(ans, v) - ans.begin();
            if (idx == ans.size()) ans.push_back(v);
            else ans[idx] = v;
        }

        return ans.size();
    }
};