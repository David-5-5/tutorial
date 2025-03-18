#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int numWays(int steps, int arrLen) {
        
        const int mod = 1e9 + 7;
        int right = min(steps/2+1, arrLen);

        vector<vector<int>> memo(steps+1, vector<int>(right, -1));

        auto dfs = [&](this auto&& dfs, int i, int j) {
            if (i==0) return j==0?1:0;

            auto& res = memo[i][j];
            if (res != -1) return res;

            return res = ((long)dfs(i-1, j) + (j>0?dfs(i-1,j-1):0) + (j+1<right?dfs(i-1,j+1):0))%mod;
        };

        return dfs(steps, 0);
    }
};