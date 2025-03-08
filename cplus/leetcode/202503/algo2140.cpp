#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  一维 DP
class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        
        vector<long> memo(n, -1);
        auto dfs = [&](this auto&& dfs, int i) -> long {
            if (i >= n) return 0;

            auto& res = memo[i];
            if (res != -1) return res;

            return res = max(dfs(i+1), questions[i][0] + dfs(i+1+questions[i][1]));
        };

        return dfs(0);        

    }
};