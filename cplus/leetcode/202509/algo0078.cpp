#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // 迭代 复习，同 python
        vector<vector<int>> ans; ans.push_back({});
        int n = nums.size();
        for (int i = 0; i<n; ++i) {
            vector<vector<int>> ext;
            for (auto sub: ans) {
                sub.push_back(nums[i]); ext.push_back(sub);
            }
            ans.insert(ans.end(), ext.begin(), ext.end());
        }

        return ans;
    }


};