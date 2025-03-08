#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  一维 DP
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        // 自行解答
        int n = questions.size();
        
        vector<long> memo(n, -1);
        auto dfs = [&](this auto&& dfs, int i) -> long {
            if (i >= n) return 0;

            auto& res = memo[i];
            if (res != -1) return res;

            auto& x = questions[i];
            return res = max(dfs(i+1), x[0] + dfs(i+1+x[1]));
        };

        return dfs(0); 

    }
};