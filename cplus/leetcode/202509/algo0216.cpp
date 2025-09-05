#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.4 组合型回溯
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        // 自行解答
        vector<vector<int>> ans;
        auto dfs = [&](this auto&& dfs, int left, vector<int>& res) -> void {
            if (res.size()>k) return;
            if (left == 0) {
                if (res.size() == k) ans.push_back(res);
                return;
            }
            // if (res.size()>k) return;    // 剪枝，但是性能未提升
            int begin = res.size()?res.back()+1:1;
            // 每个元素取值1~9之间
            for (int i=begin; i<=min(9,left); ++i) {
                res.push_back(i); dfs(left-i, res); res.pop_back();
            }
        };
        vector<int> res; dfs(n, res);
        return ans; 
    }
};