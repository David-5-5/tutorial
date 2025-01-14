#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 脑筋急转弯
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        // 连续的最大值就是答案
        int mx = ranges::max(nums);
        int ans = 0, res = 0;
        for (int v:nums) {
            if (v == mx) res += 1;
            else res = 0;
            ans = max(res, ans);
        }
    }
};