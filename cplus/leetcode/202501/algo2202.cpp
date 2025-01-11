#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 思维题 - 从特殊到一般
class Solution {
public:
    int maximumTop(vector<int>& nums, int k) {
        // 自行解答，分类讨论
        if (k %2 == 1 and nums.size() == 1) return -1; // 执行 k 次，nums 为空

        if (k > nums.size()) 
            return *max_element(nums.begin(), nums.end());
        
        if (k > 1) return max(*max_element(nums.begin(), nums.begin() + k - 1), nums[k]);        
        else return nums[k]; // 当 k = 0 或 k = 1 时，分别 nums[0] 或 nums[1]

    }
};