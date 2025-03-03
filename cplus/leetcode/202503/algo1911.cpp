#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  状态机 DP - 基础
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        // 自行解答
        int n = nums.size();
        vector<vector<long>> memo(n, vector<long>(2, -1));
        auto dfs = [&](this auto&& dfs, int i, int odd) -> long {
            if (i == n) return 0;

            auto& res = memo[i][odd];
            if (res != -1) return res;
            res = dfs(i+1, odd);
            res = max(res, (odd==1?nums[i]:-nums[i]) + dfs(i+1, odd^1));
            return res;
        };

        return dfs(0, 1);  // param 从 0 开始，1，上一个是奇数
    }
};