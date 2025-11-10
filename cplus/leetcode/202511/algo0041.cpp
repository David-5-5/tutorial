#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.4 原地修改
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // 自行解答
        nums.push_back(0);
        int n = nums.size();
        for (int i=0; i<n; i++) {
            while (nums[i] > 0 && nums[i]<n && nums[i]!=nums[nums[i]])
                swap(nums[i], nums[nums[i]]);
        }
        for (int i=1; i<n; i++) if (nums[i]!=i) return i;

        return n;
    }
};