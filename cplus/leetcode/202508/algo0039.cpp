#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // 自行解答 - 回溯
        vector<vector<int>> ans; int n = candidates.size();
        auto dfs = [&](this auto&& dfs, int i, int sum, vector<int>& cur) -> void {

            if (sum == target) {ans.push_back(cur);return;}
            if (sum > target) return;

            for (int j = i; j<n; j++) {
                sum += candidates[j]; cur.push_back(candidates[j]);
                dfs(j, sum, cur);   // j 持续增加，保持结果唯一
                sum -= cur.back(); cur.pop_back();     // 恢复现场
            }
        };
        vector<int> cur;
        dfs(0, 0, cur);
        return ans;
    }
};