#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        // 自行解答 - 时间复杂度 O(n^2logn) 应该还有更优解
        int ans = 0, n = nums.size(); sort(nums.begin(), nums.end());
        for (int i = 0; i<n-2; ++i) for (int j=i+1; j<n-1; ++j) {
            auto r = lower_bound(nums.begin()+j+1, nums.end(), nums[i]+nums[j]);
            ans += r - nums.begin()-j-1;
        }
        return ans;
    }
};