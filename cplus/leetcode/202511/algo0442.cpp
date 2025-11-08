#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.4 原地修改
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // 题解的思路比我的更好，不需要额外空间，防止当前找位置的数
        int n = nums.size();
        for (int i=0; i<n; ++i) {
            // 这语句有些抽象
            while (nums[i]!=nums[nums[i]-1]) swap(nums[i], nums[nums[i]-1]);
        }
        vector<int> ans;
        for (int i=0; i<n; ++i) if (nums[i]!=i+1) ans.push_back(nums[i]);
        return ans;
    }
};