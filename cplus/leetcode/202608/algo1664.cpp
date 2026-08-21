#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int odd_sum = 0, even_sum = 0, n = nums.size();
        for (auto i=0; i<n; i++) {
            if (i % 2) odd_sum += nums[i];
            else even_sum += nums[i];
        }

        int pre_odd = 0, pre_even = 0, ans = 0;
        for (auto i=0; i<n; i++) {
            if (i % 2) {
                if (pre_odd + even_sum - pre_even == pre_even + odd_sum - nums[i] - pre_odd)
                    ans ++;
                pre_odd += nums[i];
            } else {
                if (pre_even + odd_sum - pre_odd == pre_odd + even_sum - nums[i] - pre_even)
                    ans ++;                
                pre_even += nums[i];
            }
        }        

        return ans;
    }
};