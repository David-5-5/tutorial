#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 旋转数组
        int l = -1, r = nums.size() - 1;
        while (l+1 < r) {
            auto m = (l + r) / 2;
            if (nums[m] == nums[r]) r -= 1; 
            else if (nums[m] < nums[r]) r = m; 
            else l = m;
        }
        // r 数组的最小值下标
        if (r!=0 && target>=nums[0]) { 
            // r == 0, 表明这个数组是有序数组, begin()~begin()+r 为空数组
            auto it = lower_bound(nums.begin(), nums.begin() + r, target);     
            if (it != nums.begin() + r && *it == target) return it - nums.begin();
        } else {
            auto it = lower_bound(nums.begin() + r, nums.end(), target);
            if (it != nums.end() && *it == target) return it - nums.begin();
        }
        return -1;
    }
};