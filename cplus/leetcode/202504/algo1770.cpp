#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  区间 DP
class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        // 自行解答，记忆化搜索。dp 还不知道怎么写
        int m = multipliers.size(), n = nums.size();

        vector<vector<int>> memo(m, vector<int>(m, -1));
        auto dfs = [&](this auto&& dfs, int i, int j) -> int{
            if (i+j==m) return 0;
            auto& res = memo[i][j];
            if (res != -1) return res;
            
            auto& mul = multipliers[i+j];
            return res = max(nums[i]*mul + dfs(i+1, j), nums[n-j-1]*mul + dfs(i, j+1));
        };
        return dfs(0,0);
    }
};