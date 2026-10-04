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

    vector<int> findDiagonalOrder2(vector<vector<int>>& nums) {
        // Diagonal 按行从大到小遍历，并按 r + c 为关键字分组
        int m = nums.size(), mx = 0, mx_c = 0;

        map<int, vector<int>> grps;
        for (int r=m-1; r>=0; r--) {
            for (int c=0; c<nums[r].size(); c++) {
                grps[r+c].emplace_back(nums[r][c]);
            }
        }
        vector<int> ans;
        for (auto &[_, sub]: grps) {
            // 按照 r + c 从小到大合并分组
            ans.insert(ans.end(), sub.begin(), sub.end());
        }
        
        return ans;
    }
};