#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    vector<int> makeParityAlternating(vector<int>& nums) {

        int n = nums.size(), cnt = 0;
        if (n == 1) return {0, 0};
        int g_mx = ranges::max(nums), g_mn = ranges::min(nums);        
        
        auto calulate = [&] (int target) -> vector<int> {
            int mn = INT_MAX, mx = INT_MIN, ops = 0;
            for (int i=0; i<n; i++) {
                auto x = nums[i];
                if (((nums[i] - i) & 1) != target) {
                    ops ++;
                    if (x == g_mx) x --;
                    else if (x == g_mn) x ++;
                }

                mn = min(mn, x);
                mx = max(mx, x);
            }

            return {ops, max(mx - mn,1)};
        };
        
        return min(calulate(0), calulate(1));
    }
};