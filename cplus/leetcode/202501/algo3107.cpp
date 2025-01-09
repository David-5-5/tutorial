#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 其他数学贪心
class Solution {
public:
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        // 自行解答
        sort(nums.begin(), nums.end());
        int mid = nums.size() / 2;
        long ans = 0; // 使用 long 避免越界

        if (nums[mid] > k) {
            while (mid >= 0) {
                if (nums[mid] <= k) break;
                ans += nums[mid--] - k;
            }
        }else if (nums[mid] < k) {
            while (mid < nums.size()) {
                if (nums[mid] >= k) break;
                ans += k - nums[mid++];
            }
        }
        return ans;
    }
};