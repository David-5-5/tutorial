#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        long long ans = 0; int l = 0, n = nums.size();
        for (int r=0; r<n; r++) {
            if (r == 0 || nums[r-1] == nums[r]) l = r;
            ans += r - l + 1;
        }
        return ans;
    }
};