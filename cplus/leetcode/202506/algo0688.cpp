#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 15. 概率/期望 DP
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        const vector<pair<int,int>> dirs = {{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}};

        // vector memo(n, vector<double>(n, -1.0));
        unordered_map<int, double> memo;
        auto dfs = [&](this auto&& dfs, int r, int c, int l) -> double {
            if (r<0 || r>=n || c<0 || c>=n) return 1.0;
            
            int mask = l << 10 | r << 5 | c;
            if (memo.count(mask)) return memo[mask];

            double res = 0;
            for (auto& [x, y] : dirs) {
                res += 0.125 * dfs(r+x, c+y, l-1);
            }
            return memo[mask] = res;
        };

        return dfs(row, column, k);
    }
};