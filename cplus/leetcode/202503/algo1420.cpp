#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        // 自行解答
        const int mod = 1e9 + 7;

        vector<vector<vector<int>>> memo(n, vector<vector<int>>(m+1, vector<int>(k+1, -1)));
        auto dfs = [&](this auto&& dfs, int i, int j, int l) -> int {
            if (l<0) return 0;
            if (i == n) return l==0?1:0;

            auto& res = memo[i][j][l];

            if (res != -1) return res;

            res = 0;
            for (int v=1; v<=m; v++) {
                res = (res + dfs(i+1, max(j, v), l-(j<v))) % mod;
            }

            return res;
        };
        
        return dfs(0, 0, k);

    }
};