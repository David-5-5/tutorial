#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        // 自行解答
        int n = nums.size(), ans = 2;
        int prev = 2;
        for (int i=2; i<n; ++i) {
            if (nums[i] == nums[i-1] + nums[i-2]) {
                int cur = prev + 1;
                ans = max(ans, cur); prev = cur;
            }
        }
        return ans;
    }


};