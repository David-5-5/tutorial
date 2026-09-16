#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int mx = *max_element(nums.begin(), nums.end()), n = nums.size();
        vector pres(n+1, vector<int>(mx+1));

        for (int i=0; i<n; i++) {
            for (int c = 1; c<=mx; c++)
                pres[i+1][c] = pres[i][c] + (c==nums[i]?1:0);
        }

        vector<int> ans;
        for (auto& q: queries) {
            auto & l = q[0], & r = q[1];
            int prev = -1, val = mx;
            for (int c=1; c<=mx; c++) if (pres[r+1][c] - pres[l][c]) {
                if (prev != -1) val = min(val, c-prev);
                prev = c;
            }
            ans.emplace_back(val==mx?-1:val);
        }

        return ans;

    }
};