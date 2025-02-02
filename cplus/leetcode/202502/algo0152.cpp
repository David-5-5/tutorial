#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 最大子数组和
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 参考题解
        vector<long> maxF(nums.size()), minF(nums.size());
        maxF[0] = nums[0], minF[0] = nums[0];

        for (int i=1; i<nums.size(); i++) {
            maxF[i] = max(maxF[i-1]*nums[i], max(minF[i-1]*nums[i], (long)nums[i]));
            minF[i] = min(maxF[i-1]*nums[i], min(minF[i-1]*nums[i], (long)nums[i]));
            
        }

        return *max_element(maxF.begin(), maxF.end());   
    }
};