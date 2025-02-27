#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        
        int n = nums.size();

        vector<int> pre_s(n+1, 0);
        for (int i=0; i<n; i++) pre_s[i+1] = pre_s[i] + nums[i];

        auto avg = [&](int l, int r) -> double {
            return (pre_s[r] - pre_s[l]) * 1.0 / (r - l);
        };

        vector<vector<double>> memo(n, vector<double>(k+1, -1.0));
        auto dfs = [&] (this auto&& dfs, int i, int j) ->double {
            if (i == n) return 0;
            if (j == 0) return INT_MIN;

            auto& res = memo[i][j];
            if (res != -1.0) return res;
            
            res = 0.0;
            for (int x=i; x<n; x++) {
                res = max(res, avg(i, x+1) + dfs(x+1, j-1));
                cout << res << endl;
            }
            return res;
        };

        return dfs(0, k);
    }
};