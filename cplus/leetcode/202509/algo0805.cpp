#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.8 折半枚举
class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        // 参考题解 - 折半枚举 - 边界条件还是很容易弄错
        int n = nums.size(); 
        if (n == 1) return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (auto& x : nums) x = x*n - sum;
        
        int mask4l = 1 << (n/2), mask4r = 1 << (n-n/2);
        
        unordered_set<int> left;

        for (int mask = 1; mask<mask4l; ++mask) {
            auto tot = 0;
            for (int j=0; j<n/2; ++j) if ((mask>>j)&1)
                tot += nums[j];
            if (tot == 0) return true;
            left.insert(tot);
        }

        int right_tot = accumulate(nums.begin()+n/2, nums.end(), 0);
        for (int mask = 1; mask<mask4r; ++mask) {
            auto tot = 0;
            for (int j=0; j<n-n/2; ++j) if ((mask>>j)&1)
                tot += nums[j+n/2];
            
            if (tot == 0 || (tot != right_tot && left.count(-tot))) return true;
        }
        return false;
        
    }
};