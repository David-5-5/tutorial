#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        // 自行解答
        long long ans = 0; sort(nums.begin(), nums.end());
        for (auto it=nums.begin(); it!=nums.end(); ++it) {
            auto r = ranges::upper_bound(nums, upper-*it);
            auto l = ranges::lower_bound(nums, lower-*it);
            ans += r - l;
            if (it >= l && it < r) ans --;  // i != j 排除自身的配对的数量
        }
        return ans/2;        
    }

    long long countFairPairs2(vector<int>& nums, int lower, int upper) {
        // 参考题解, 更加清晰，不需要/2
        long long ans = 0; sort(nums.begin(), nums.end());
        for (int i = 0; i<nums.size(); ++i) {
            auto r = upper_bound(nums.begin(), nums.begin()+i, upper-nums[i]);
            auto l = lower_bound(nums.begin(), nums.begin()+i, lower-nums[i]);
            ans += r - l;
        }
        return ans;  
    }    

    long long countFairPairs3(vector<int>& nums, int lower, int upper) {
        // 参考题解, nums排序后 三指针，lower - nums[l] <= nums[i] <=upper-nums[r]
        // 随着nums[i] 增加， nums[l] nums[r] 都减少，即 l， r 都减少
        long long ans = 0; sort(nums.begin(), nums.end());
        int n = nums.size(), l = n, r = n;  // 这里的取值太有学问了
        for (int i = 0; i<n; ++i) {
            while (r && nums[i] > upper-nums[r-1]) r--;
            while (l && nums[i] >= lower-nums[l-1]) l--;
            ans += min(r, i) - min(l, i);   // 同二分的 lower_bound(nums.begin(), nums.begin()+i, **);
        }
        return ans;  
    }        
};