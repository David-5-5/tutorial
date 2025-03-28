#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  0.1 枚举右，维护左
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        // 自行解答 排序，双指针
        sort(nums.begin(), nums.end());
        int n = nums.size(), i = 0, j = n - 1, ans = 0;

        while (i < j) {
            if (nums[i] + nums[j] == k) {
                ans ++, i++, j--;
            } else if (nums[i] + nums[j] > k) j--;
            else i ++;
        }
        return ans;
    }
};