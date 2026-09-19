#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        // 内置方法
        sort(nums.begin(), nums.end());

        int n = nums.size(), ans = 0;
        for (int i=1; i<n; i++) {
            ans = max(ans, nums[i] - nums[i-1]);
        }
        return ans;        
    }


};