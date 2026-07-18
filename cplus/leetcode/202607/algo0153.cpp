#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int findMin(vector<int>& nums) {
        // 旋转数组 没有重复元素，二分
        if (nums[0] <= nums.back()) return nums[0];
        int l = 0, r = nums.size() - 1;
        while (l+1 < r) {
            auto m = (l + r) / 2;
            if (nums[m] <= nums[r]) r = m; //arr[m] == arr[r] 时，两部分都需要继续查找
            else l = m;
        }
        return nums[r];
    }
};