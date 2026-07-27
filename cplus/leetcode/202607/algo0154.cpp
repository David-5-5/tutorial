#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        // 数据量很小，可以暴力
        auto mn = nums[0];
        for (int i=1; i<nums.size(); i++) {
            if (nums[i] < mn) return nums[i];
        }
        return mn;      
    }

    int findMin2(vector<int>& nums) {
        // 旋转数组 重复元素 二分   比较 iv 10.03
        int l = -1, r = nums.size() - 1;
        while (l+1 < r) {
            auto m = (l + r) / 2;
            if (nums[m] == nums[r]) r -= 1; 
            else if (nums[m] < nums[r]) r = m; 
            else l = m;
        }
        return nums[r];
    }
};