#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        // 旋转数组 重复元素 类似 0154(min)
        int l = -1, r = nums.size() - 1;
        while (l+1 < r) {
            auto m = (l + r) / 2;
            if (nums[m] == nums[r]) r -= 1; 
            else if (nums[m] < nums[r]) r = m; 
            else l = m;
        }
        // nums[r] 是最小值
        auto it = lower_bound(nums.begin() + r, nums.end(), target+1);

        if (target >= nums[0]) {
            auto it = lower_bound(nums.begin(), nums.begin() + r, target + 1);
            return it != nums.begin() && *prev(it) == target;
        } else {
            auto it = lower_bound(nums.begin() + r, nums.end(), target + 1);
            return it != nums.begin()+r && *prev(it) == target;
        }

    }
};