#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        // TLE(Time Limit Extended)
        int m = nums.size(), mx = 0;
        for (int i=0; i<m; i++) {
            mx = max(mx, (int)(i + nums[i].size()));
        }
        vector<int> ans;

        for (int s = 0; s<mx; s++) {
            for (int r = min(s-0, m-1); r>=0; r--) {
                auto c = s - r; if (c < 0) break;
                if (c >= nums[r].size()) continue;
                ans.emplace_back(nums[r][c]);
            }
        }

        return ans;
    }


};