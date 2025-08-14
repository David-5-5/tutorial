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
    
};