#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        // 自行解答
        vector<vector<vector<int>>> memo(m,vector<vector<int>>(n+1,vector<int>(target+1, -1)));

        auto dfs = [&] (this auto&& dfs, int i, int p, int l) ->int {
            if (l < 0) return INT_MAX/2;
            if (i < 0)
                if (l == 0) return 0;
                else return INT_MAX/2;      // 使用 INT_MAX 做加法越界

            auto& res = memo[i][p][l];
            if (res != -1) return res;
            
            res = INT_MAX/2;
            if (houses[i]!=0) return res = dfs(i-1, houses[i], l-(houses[i]!=p));
            
            for (int c=1; c<=n; c++) {
                res = min(res, cost[i][c-1] + dfs(i-1, c, l - (c!=p)));
            }
            return res;
        };

        int ans = dfs(m-1, 0, target);
        return (ans >= INT_MAX/2) ? -1 : ans;

    }
};