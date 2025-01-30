#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 打家劫舍
class Solution {
public:
    // 参考题解，特殊处理 nums[0] 调用 198 空间优化的 dp 写法
    int rob198(vector<int>& nums, int start, int end) {
        int f0 = 0, f1 = 0;
        for (int i=start; i<end; i++) {
            int new_f = max(f1, f0 + nums[i]);
            f0 = f1;
            f1 = new_f;
        }
        return f1;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        return max(nums[0] + rob198(nums, 2, n-1), rob198(nums, 1, n));
    }
};