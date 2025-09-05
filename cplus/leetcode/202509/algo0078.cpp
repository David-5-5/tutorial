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

    vector<vector<int>> subsets2(vector<int>& nums) {
        // 自行解答 递归回溯
        vector<vector<int>> ans; int n = nums.size();

        auto dfs = [&] (this auto&& dfs, int i, vector<int>& path) -> void  {
            if (i == n) {
                ans.push_back(path);
                return;
            }

            dfs(i+1, path);               // 不选
            path.push_back(nums[i]);    // 选
            dfs(i+1, path);
            path.pop_back();            // 恢复现场
        };

        vector<int> path;
        dfs(0, path);
        return ans;     
    }
    
};