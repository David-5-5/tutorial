#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.6 有重复元素的回溯
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // 自行解答 递归回溯
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans; int n = nums.size();

        auto dfs = [&] (this auto&& dfs, int i, vector<int>& path) -> void  {
            if (i == n) {
                ans.push_back(path);
                return;
            }
            int j = i;
            while (j<n && nums[j]==nums[i]) j++;

            dfs(j, path);                       // 不选
            for (int _=0; _<j-i; ++_) {
                path.push_back(nums[i]);        // 选
                dfs(j, path);
            }
            for (int _=0; _<j-i; ++_) path.pop_back();  // 恢复现场
        };

        vector<int> path;
        dfs(0, path);
        return ans;
    }


    
};