#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 约束划分个数
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();

        if (n < d) return -1;

        auto mx = [&](int l, int r) -> int {
            return *max_element(jobDifficulty.begin()+l, jobDifficulty.begin()+r);
        };

        vector<vector<int>> memo(n, vector<int>(d+1, -1));
        auto dfs = [&] (this auto&& dfs, int i, int j) ->int {
            if (j < 0) return INT_MAX/2;
            if (i == n)
                if (j == 0) return 0;
                else return INT_MAX/2;      // 使用 INT_MAX 做加法越界

            auto& res = memo[i][j];
            if (res != -1) return res;
            
            res = INT_MAX/2;
            for (int x = i; x<n; x++) {  // 不能超过 jobDifficulty 长度
                res = min(res, mx(i, x+1) + dfs(x+1, j-1));
            }
            
            return res;
        };

        return dfs(0, d);   

    }
};