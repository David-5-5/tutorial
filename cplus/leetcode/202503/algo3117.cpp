#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        // 2025.9.5 复习
        // 参考题解 记忆化搜索，三个变量压缩到一个变量，使用 map 代替数组，减少存储空间
        // and_ 值的范围很大，值的数量有限 <= logU
        const int INF = INT_MAX / 2; // 除 2 防止下面 + nums[i] 溢出

        int m = nums.size(), n = andValues.size();

        unordered_map<long long, int> memo;
        auto dfs = [&](this auto&& dfs, int i, int j, int and_) -> int {
            if (m-i < n-j) return INF;
            if (j == n) return i == m? 0 : INF;
            and_ &= nums[i];    // 先计算 and_
            
            long long mask = (long long) i<<36 | (long long) j << 32 | and_;
            if (memo.contains(mask)) return memo[mask];

            int res = dfs(i+1, j, and_); // 不分割
            if (and_ == andValues[j])
                res = min(res, nums[i] + dfs(i+1, j+1, -1));

            return memo[mask] = res;
        };

        int ans = dfs(0, 0, -1);    // -1 所有位都是 1
        return ans < INF ? ans : -1;
    }
};