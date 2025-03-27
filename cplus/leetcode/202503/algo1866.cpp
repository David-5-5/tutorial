#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int rearrangeSticks(int n, int k) {
        // 暴力，时间复杂度 O(n!*k)，需要优化到 O(nk)/O(nklogn)

        const int mod = 1e9 + 7;
        unordered_set<int> visited;

        auto dfs = [&](this auto&& dfs, int l, int m) -> int {
            if (l<0) return 0;
            if (visited.size() == n) return l==0?1:0;

            int res = 0;
            for (int i=1; i<=n; i++) {
                if (visited.count(i)) continue;
                visited.emplace(i);
                res += dfs(l-(i>m?1:0), max(i, m));
                visited.erase(i);
            }
            return res % mod;
        };

        return dfs(k, 0);   
        
    }

    int rearrangeSticks2(int n, int k) {
        // 自行解答，优化
        // 对于 n 根木棍，不管怎么选，最后一根木棍肯定需要选择，
        // 因此思路从长度为 n 的木棍，从大到小进行递归选择，
        // 因此递归的入口是 dfs(n-1, k-1), 还需要选择 k - 1 根
        // 对于 n - 1 根，有两种方法，即 n - 1 放在最前面，放在后面两种放法
        // 对于 第 i 根， 放在最前面的方法有 一种， 放在后面的放法有 n-i种，
        //              由于从大到小遍历，后面的棍子都比它长，可以放在后面 n-i 根任意一根的后面
        // 因此最终的状态转移方程为
        // dfs(i, j) = dfs(i-1, j-1) + dfs(i-1,j) * (n-i)
        const int mod = 1e9 + 7;

        vector<vector<int>> memo(n+1, vector<int>(k, -1));
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i < j || j <0) return 0;
            if (i == 0) return 1;

            auto& res = memo[i][j];

            if (res != -1) return res;

            return res = ((long)dfs(i-1, j-1) + ((long)dfs(i-1, j) * (n-i)) % mod) % mod;
            
        };

        return dfs(n-1, k-1);

    }
};