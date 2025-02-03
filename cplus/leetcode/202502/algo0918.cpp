#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最大子数组和
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // 参考题解
        int n = nums.size();
        int tot = accumulate(nums.begin(), nums.end(), 0);

        int cur_max = INT_MIN, cur_min = 0;
        int ans_max = INT_MIN, ans_min = 0;


        for (int i=0; i < n; i++) {
            cur_max = max(cur_max, 0) + nums[i]; // 至少包含一个元素
            ans_max = max(ans_max, cur_max);
            
            cur_min = min(cur_min, 0) + nums[i];
            ans_min = min(cur_min, ans_min);
        }
        return tot==ans_min?ans_max: max(ans_max, tot-ans_min);
    }
};