#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        // 旋转数组 重复元素 类似 0154(min)
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int m = (l + r) / 2;            
            if (nums[m] == target || nums[l] == target || nums[r] == target)
                return true;
            // 分类讨论
            if (nums[m] == nums[l] && nums[m] == nums[r]) {
                // 都相等，无法判断，缩小区间，最差情况 O(N)
                l ++; r --;
            } else if (nums[l] < nums[r]) { //单调
                // 严格单调
                auto it = upper_bound(nums.begin() + l, nums.begin() + r + 1, target);
                if (it != nums.begin() + l && *prev(it) == target) return true;
                else return false;
            } else if (nums[m] >= nums[l]) { 
                // nums[m] >= nums[l] >= nums[r]  结合图形判断
                // 当 target < nums[m] 进入 [l, m-1] 区间继续
                // 当 target > nums[m] || target < nums[r] 进入 [m+1, r] 区间
                if (target > nums[m] || target < nums[r]) l = m + 1;
                else r = m - 1;
            } else {
                // nums[l] >= nums[r] >= nums[m]  结合图形判断
                // 当 target < nums[m] || target > nums[r] 进入 [l, m-1] 区间继续
                // 当 target > nums[r] 进入 [m+1, r] 区间
                if (target < nums[m] || target > nums[r]) r = m - 1;
                else l = m + 1;
            }
        }
        return false;     
    }
};