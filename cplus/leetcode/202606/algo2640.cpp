#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> findPrefixScore(vector<int>& nums) {
        int mx = 0, n = nums.size();
        vector<long long> ans(n);
        for (int i=0; i<n; i++) {
            mx = max(mx, nums[i]);
            ans[i] = mx + nums[i] + (i?ans[i-1]:0);
        }
        return ans;
    }
};