#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  8.2其他区间 DP
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        // 参考题解，基础算法精讲22，区间DP
        int n = values.size();

        vector<vector<int>> memo(n, vector<int>(n, INT_MAX));
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {
            if (i + 1 == j) {
                return 0;
            }
            auto& res = memo[i][j];
            if (res!=INT_MAX) return res;
            for (int k=i+1; k<j; k++) {
                res = min(res, dfs(i,k) + dfs(k,j) + values[i]*values[k]*values[j]);
            }
            return res;

        };

        return dfs(0, n-1);
        
    }
};