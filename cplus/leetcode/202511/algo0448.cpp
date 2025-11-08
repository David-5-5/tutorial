#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 单序列双指针 3.4 原地修改
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // 同 442
        int n = nums.size();
        for (int i=0; i<n; ++i) {
            // 这语句有些抽象 nums[i]-1 因为值 [1,n] 数组下标 [0,n-1]
            while (nums[i]!=nums[nums[i]-1]) swap(nums[i], nums[nums[i]-1]);
        }
        vector<int> ans;
        for (int i=0; i<n; ++i) if (nums[i]!=i+1) ans.push_back(i+1);
        return ans;        
    }
};