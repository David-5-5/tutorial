#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 五、三指针
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        // 自行解答 - 通过测试案例手动模拟并找出规律
        int l = 0, r = -1, ans = 0, n = nums.size();
        for (int i=0; i<n; ++i)  {
            if (nums[i] > right) {
                l = i+1, r = i; continue;
            } else if (nums[i] >= left) r = i;
            ans += r - l + 1;
        }

        return ans;
    }
};