#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  一维 DP
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // 自行解答，记忆化搜索超时 python 记忆化搜索可以通过
        int n = days.size(); 
        vector<vector<int>> memo(n, vector<int>(366, -1));

        auto dfs = [&](this auto&& dfs, int i, int v) -> int {
            if (i == n) return 0;
            auto res = memo[i][v];
            if (res != -1) return res;

            if (days[i] <= v) return res = dfs(i+1, v);
            res = costs[0] + dfs(i+1, 0);
            res = min(res, costs[1] + dfs(i+1, days[i]+6));
            res = min(res, costs[2] + dfs(i+1, days[i]+29));
            
            return res;
        };
        return dfs(0,0);
    }
};