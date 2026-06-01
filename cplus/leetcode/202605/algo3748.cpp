#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), l = 0;
        vector<long long> pres(n+1);
        
        for (int r=0; r<n; r++) {
            while (l<r && nums[l]>nums[l+1]) l++;
            pres[r+1] = pres[r] + r - l + 1;
        }

        vector<long long> ans;
        for (auto q:queries) {
            auto l = q[0], r = q[1];
            ans.push_back(pres[r+1] - pres[l]);
        }

        return ans;
    }
};