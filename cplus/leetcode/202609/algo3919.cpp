#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(); vector<int> closest(n), pres(n), sufs(n);
        closest[0] = 1, closest[n-1] = n-2;
        for (int i=1; i<n-1; i++) {
            closest[i] = abs(nums[i]-nums[i-1]) <= abs(nums[i]-nums[i+1])?i-1:i+1;
        }
        for (int i=0; i<n-1; i++) {
            pres[i+1] = pres[i] + (closest[i]==i+1?1:abs(nums[i+1]-nums[i]));
            sufs[n-i-2] = sufs[n-i-1] + (closest[n-i-1]==n-i-2?1:abs(nums[n-i-2]-nums[n-i-1]));
        }

        int m = queries.size(); vector<int> ans(m);
        for (int i=0; i<m; i++) {
            auto l=queries[i][0], r = queries[i][1];
            if (l < r) ans[i] = pres[r] - pres[l];
            else if (l > r) ans[i] = sufs[r] - sufs[l];
        }
        return ans;
    }
};