#include <bits/stdc++.h>
using namespace std;

// 1850的基础 
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // 用库函数
        next_permutation(nums.begin(), nums.end());
    }

    void nextPermutation(vector<int>& nums) {
        // 两次遍历及反转
        int i = nums.size()-2;
        while (i>=0 and nums[i]>=nums[i+1]) {   // 找到第一个顺序对
            i--;
        }
        if (i>=0) {
            int j = nums.size()-1;
            while (j>i and nums[j]<=nums[i]) {
                j--;
            }
            swap(nums[i], nums[j]);
        } 
        reverse(nums.begin()+i+1, nums.end());
    }
};