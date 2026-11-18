#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxValidPairSum(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        
        for (int i=0; i<n-k; i++) {
            ans = max(ans, nums[i] + nums[i+k]);
            nums[i+1] = max(nums[i+1], nums[i]);
        }
        return ans;
    }
};