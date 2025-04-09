#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.1 排列型 - 相邻无关
class Solution {
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        // 自行解答
        int n= mentors[0].size(), m = mentors.size();

        auto score = [&](int i, int j) ->int {
            int ans = 0;
            for (int k=0; k<n; k++) ans += (students[i][k] == mentors[j][k]);
            return ans;
        };

        vector<int> memo(1<<m, -1);
        auto dfs = [&] (this auto&& dfs, int state) -> int {
            if (state == 0) return 0;
            auto& res = memo[state];
            if (res != -1) return res;
            res = 0;
            // 计算包含一个的个数，减少一个递归参数
            int i = m - __builtin_popcount(state);  
            for (int j=0; j<m; j++) if ((state >> j) & 1) 
                res = max(res, score(i, j) + dfs(state - (1 << j))) ;

            return res;
        };

        return dfs((1<<m)-1);
    }
};