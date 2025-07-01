#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        // 自行解答
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


    long long maximumProduct2(vector<int>& nums, int m) {
        // 参考题解 不需要特判 m = 1 时 最大值 或 最小值相乘 一定是结果
        long long ans = LLONG_MIN;
        int mx=INT_MIN, mn = INT_MAX;
        for (int r=m-1; r<nums.size(); ++r) {
            mx = max(mx, nums[r-m+1]), mn = min(mn, nums[r-m+1]);
            long long x = nums[r];
            // 看上去好看，但是性能差，特别是数据量较多的情况，出现过超时
            // ans = max({ans, x * mx, x * mn});
            ans = max(ans, x * mx); ans = max(ans, x * mn);
        }
        return ans;
    }
};