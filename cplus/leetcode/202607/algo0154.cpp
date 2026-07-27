#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        // 数据量很小，可以暴力
        auto mn = nums[0];
        for (int i=1; i<nums.size(); i++) {
            if (nums[i] < mn) return nums[i];
        }
        return mn;      
    }


};