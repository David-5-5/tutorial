#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        // 自行解答 使用 942 ID...ID 排列
        sort(nums.begin(), nums.end());
        int mn = 0, mx = nums.size(), even = 1;
        vector<int> ans;
        while (mn < mx)
            if (even) ans.push_back(nums[mn++]), even ^= 1;
            else ans.push_back(nums[--mx]), even ^= 1;
        return ans;
    }
};
