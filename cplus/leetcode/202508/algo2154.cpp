#include <bits/stdc++.h>
using namespace std;

// 位运算 - 基础题
class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        // 排序和遍历，开销主要在排序 时间复杂度 O(NlogN)
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();i++){
            if(original==nums[i]){
                original*=2;
            }
        }
        return original;
    }


    int findFinalValue2(vector<int>& nums, int original) {
        // 哈希表，时间复杂度O(N)
        int mask = 0;
        for(auto & num : nums){
            if(num % original == 0){
                int k = num / original;
                if ((k & (k-1)) == 0) mask |= k;
            }
        }
        mask = ~ mask;
        return original * (mask & (-mask)); // lowbit
    }
        
};