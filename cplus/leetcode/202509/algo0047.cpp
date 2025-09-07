#include <bits/stdc++.h>
using namespace std;

// 2025.9.7 复习 重复数据 全排列
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // 参考题解 
        int n = nums.size(); sort(nums.begin(), nums.end());
        
        vector<vector<int>> ans;
        vector<int> vis(n), path;
        auto dfs = [&] (this auto&& dfs, vector<int>& path) -> void {
            if (path.size() == n) {
                ans.push_back(path); return;
            }

            for (int i=0; i<n; ++i) {
                if (vis[i]) continue; 
                // 确保重复元素依次使用
                if (i>0 && nums[i-1]==nums[i] && vis[i-1]) continue;
                path.push_back(nums[i]); vis[i] = true;
                dfs(path);
                path.pop_back(); vis[i] = false;
            }

        };
        
        dfs(path); return ans;
    }
};