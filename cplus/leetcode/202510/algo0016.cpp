#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.1 相向双指针
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        // 自行解答 - 两数之和进阶
        int n = nums.size(), ans = INT_MAX/2;
        sort(nums.begin(), nums.end());
        for (int m=1; m<n-1; ++m) {
            int l = 0, r = n-1;
            while (true) {
                if (l == m || r == m) break;
                if (nums[l] + nums[m] + nums[r] == target) return target;
                else if (nums[l] + nums[m] + nums[r] > target) {
                    if (abs(ans-target) > abs(nums[l] + nums[m] + nums[r] - target))
                        ans = nums[l] + nums[m] + nums[r];
                    r--;
                } else {
                    if (abs(ans-target) > abs(nums[l] + nums[m] + nums[r] - target))
                        ans = nums[l] + nums[m] + nums[r];
                    l++;
                }
            }
        }
        return ans;
    }
};