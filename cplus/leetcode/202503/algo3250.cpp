#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        const int mod = 1e9 + 7;
        int n = nums.size(), mx = ranges::max(nums);

        vector<vector<vector<int>>> memo(n+1, vector<vector<int>>(mx+1, vector<int>(mx+1, -1)));

        auto dfs = [&](this auto&& dfs, int i, int s, int t) -> int {
            if (i == n) return 1;
            
            auto& res = memo[i][s][t];
            
            if (res != -1) return res;

            res = 0;
            for (int n_s=s; n_s<=nums[i]; n_s++) {
                int n_t = nums[i] - n_s;
                if (n_t <= t) res = ((long)res + dfs(i+1, n_s, n_t)) % mod;
            }
            
            return res;
        };

        return dfs(0, 0, mx);

    }
};