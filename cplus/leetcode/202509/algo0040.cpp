#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.6 有重复元素的回溯
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // 自行解答 递归回溯 基于子集 leetcode 90
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans; int n = candidates.size();

        auto dfs = [&] (this auto&& dfs, int i, int sum, vector<int>& path) -> void  {
            if (sum == target) ans.push_back(path);
            if (i == n || sum >= target)  return;
            
            int j = i;
            while (j<n && candidates[j]==candidates[i]) j++;

            dfs(j, sum, path);                       // 不选
            for (int _=0; _<j-i; ++_) {
                sum += candidates[i];
                path.push_back(candidates[i]);        // 选
                dfs(j, sum, path);
            }
            for (int _=0; _<j-i; ++_) path.pop_back();  // 恢复现场
        };

        vector<int> path;
        dfs(0, 0, path);
        return ans;
    }

    vector<vector<int>> combinationSum2_2(vector<int>& candidates, int target) {
        // 参考 491 选择重复元素的做法，由于未剪枝，超时
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans; int n = candidates.size();

        auto dfs = [&] (this auto&& dfs, int i, int sum, vector<int>& path) -> void  {
            
            if (i == n) {
                if (sum == target) ans.push_back(path);
                return;
            } 
            
            // sum += candidates[i];
            if (path.empty() || candidates[i] != path.back()) {
                dfs(i+1, sum, path);
            }

            path.push_back(candidates[i]);        // 选
            dfs(i+1, sum+candidates[i], path);
            path.pop_back();  // 恢复现场


        };

        vector<int> path;
        dfs(0, 0, path);
        return ans;
    }
};