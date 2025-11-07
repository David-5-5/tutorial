#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.4 原地修改
class Solution {
public:
    void sortColors(vector<int>& nums) {
        // 参考题解 - 原地修改技巧
        int p0 = 0, p1 = 0;
        for (int i=0; i<nums.size(); ++i) {
            int x = nums[i];
            nums[i] = 2;
            if (x <= 1) nums[p1++] = 1; // 若前面队列中没有2，将覆盖 nums[i]
            if (x == 0) nums[p0++] = 0;
        }  
    }
};