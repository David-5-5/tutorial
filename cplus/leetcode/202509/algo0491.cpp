#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.6 有重复元素的回溯
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        // 参考题解
        vector<vector<int>> ans; int n = nums.size();

        auto dfs = [&] (this auto&& dfs, int i, vector<int>& path) -> void  {
            if (i == n) {
                if (path.size()>1) ans.push_back(path);
                return;
            } 
            
            if (path.empty() || path.back() <= nums[i]) {   // 可选
                path.push_back(nums[i]);        // 选
                dfs(i+1, path);
                path.pop_back();                // 恢复现场
            }
            // 代码简单，思维能力要求高
            if (path.empty() || path.back() != nums[i]) { // 元素相同时，不跳过
                dfs(i+1, path);
            }

        };

        vector<int> path;
        dfs(0, path);
        return ans;    
    }
};