#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  一维 DP
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // 自行解答
        int n = days.size();
        vector<vector<int>> memo(n, vector<int>(366, -1));

        auto dfs = [&](this auto&& dfs, int i, int v) -> int {
            if (i >= n || v > 365) return 0;
            auto& res = memo[i][v];
            if (res != -1) return res;

            if (days[i] <= v) return res = dfs(i+1, v);
            res = costs[0] + dfs(i+1, 0);
            res = min(res, costs[1] + dfs(i+1, days[i]+6));
            res = min(res, costs[2] + dfs(i+1, days[i]+29));
            
            return res;
        };
        return dfs(0,0);
    }

    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // 参考题解 降维
        unordered_set dayset(days.begin(), days.end());     // set
        vector<int> memo(366, -1);

        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i > 365) return 0;
            auto& res = memo[i];
            if (res != -1) return res;
            
            if (!dayset.count(i)) return res = dfs(i+1);
            res = costs[0] + dfs(i+1);
            res = min(res, costs[1] + dfs(i+7));
            res = min(res, costs[2] + dfs(i+30));
            
            return res;
        };
        return dfs(1);
    }

};