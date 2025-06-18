#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        long long ans = LLONG_MIN;
        if (m == 1) {
            for (auto& v:nums) {
                ans = max(ans, (long long) v * v);
            }
            return ans;
        }

        int l = 0, mx=nums[l], mn = nums[l];
        for (int r=m-1; r<nums.size(); ++r) {
            ans = max(ans, (long long) nums[r] * mx);
            ans = max(ans, (long long) nums[r] * mn);
            l ++;
            mx = max(mx, nums[l]); mn = min(mn, nums[l]);
        }
        return ans;
    }
};