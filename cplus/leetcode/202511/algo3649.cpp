#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.2 同向双指针
class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        // 参考题解，关键是要理解绝对值的意义
        for (auto &v:nums) v = abs(v);
        sort(nums.begin(), nums.end());
        int l = 0, n = nums.size();
        long long ans = 0;
        for (int r=0; r < n; ++r) {
            // max(|a-b|,|a+b|) >= max(|a|,|b|)
            // min(|a-b|,|a+b|) <= min(|a|,|b|) 
            // 令 a b 都为正数，a < b 则 2a >= b
            while (nums[l]*2 < nums[r]) // 2a >= b
                l ++;
            ans += r - l;
        }
        return ans;   

    }
};