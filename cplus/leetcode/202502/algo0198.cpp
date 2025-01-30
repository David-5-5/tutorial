#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 打家劫舍
class Solution {
public:
    int rob(vector<int>& nums) {
        // 自行解答，静下心来用笔写一下状态转移方程
        int n = nums.size();
        vector<vector<int>> f(n, vector<int>(2));
        f[0][0] = 0, f[0][1] = nums[0];

        for (int i=1; i<n; i++) {
            f[i][0] = max(f[i-1][1], f[i-1][0]);
            f[i][1] = f[i-1][0] + nums[i];
        }

        return max(f.back()[0], f.back()[1]);    
    }


    int rob2(vector<int>& nums) {
        // 参考题解 1 维 dp
        int n = nums.size();
        vector<int> f(n+2);
        for (int i=0; i<n; i++) {
            f[i+2] = max(f[i]+nums[i], f[i+1]);
        }
        return f[n+1];
    }


    int rob3(vector<int>& nums) {
        // 记忆化搜索
        int n = nums.size();
        vector<int> memo(n, -1);

        function<int(int)> dfs = [&](int i) -> int {
            if (i < 0) return 0;
            if (memo[i] != -1)  return memo[i];

            return memo[i] = max(dfs(i-1), dfs(i-2)+nums[i]);
        };

        return dfs(n-1);
    }
};