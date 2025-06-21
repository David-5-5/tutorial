#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        if (n<3) return false;
        vector<int> suf_mx(n);
        suf_mx[n-1] = nums[n-1];
        for (int i=n-2; i; --i) suf_mx[i] = max(nums[i], suf_mx[i+1]);

        int pre_mn = nums[0];
        for (int i=1; i<n-1; ++i) {
            if (pre_mn < nums[i] && nums[i] < suf_mx[i+1]) return true;
            pre_mn = min(pre_mn, nums[i]);
        }
        return false;      
    }
};