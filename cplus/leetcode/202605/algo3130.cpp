#include <bits/stdc++.h>
using namespace std;

// 十一、优化 DP - 11.1 前缀和优化 DP
class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        // 状态转移方程参考题解
        const int mod = 1e9 + 7;
        vector memo(zero+1, vector(one+1, vector<long long>(2, -1)));   

        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> long long {

            if (i < 0 || j < 0) return 0;
            // if (i == 0 && j == 0) return 1;
            if (i == 0) return k == 1 && j <= limit;
            if (j == 0) return k == 0 && i <= limit;

            auto & res = memo[i][j][k];
            if (res != -1) return res;

            if (k == 0) return res = (mod + dfs(i-1, j, 0) + dfs(i-1, j, 1) - dfs(i-limit-1, j, 1)) % mod;
            else return res = (mod + dfs(i, j-1, 0) + dfs(i, j-1, 1) - dfs(i, j-limit-1, 0)) % mod;
        };

        return (dfs(zero, one, 0) + dfs(zero, one, 1)) % mod;
    }   

    int numberOfStableArrays2(int zero, int one, int limit) {
        const int mod = 1e9 + 7;
        // 超时 200万记录不适合 unordered_map 作为记忆化搜索的数据结构
        unordered_map<int, long long> memo;     

        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> long long {

            if (i < 0 || j < 0) return 0;
            // if (i == 0 && j == 0) return 1;
            if (i == 0) return k == 1 && j <= limit;
            if (j == 0) return k == 0 && i <= limit;

            int mask = (k << 21) | (i << 11) | j;
            if (memo.count(mask)) return memo[mask];

            if (k == 0) return memo[mask] = (mod + dfs(i-1, j, 0) + dfs(i-1, j, 1) - dfs(i-limit-1, j, 1)) % mod;
            else return memo[mask] = (mod + dfs(i, j-1, 0) + dfs(i, j-1, 1) - dfs(i, j-limit-1, 0)) % mod;
        };

        return (dfs(zero, one, 0) + dfs(zero, one, 1)) % mod;
    }

 
};