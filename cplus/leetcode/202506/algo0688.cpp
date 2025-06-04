#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 15. 概率/期望 DP
class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        // 自行解答 - 使用 unordered_map for memo
        const vector<pair<int,int>> dirs = {{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}};

        unordered_map<int, double> memo;
        auto dfs = [&](this auto&& dfs, int r, int c, int l) -> double {
            if (r<0 || r>=n || c<0 || c>=n) return 0;
            if (l == 0) return 1;
            
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


    double knightProbability2(int n, int k, int row, int column) {
        // 自行解答 - 使用 vector for memo
        const vector<pair<int,int>> dirs = {{-2,-1},{-1,-2},{1,-2},{2,-1},{-2,1},{-1,2},{1,2},{2,1}};

        vector memo(n, vector<vector<double>>(n, vector<double>(k+1, -1)));
        auto dfs = [&](this auto&& dfs, int r, int c, int l) -> double {
            if (r<0 || r>=n || c<0 || c>=n) return 0.0;
            if (l == 0) return 1.0;

            auto& res = memo[r][c][l];
            if (res >= 0) return res;
            res = 0;
            for (auto& [x, y] : dirs) {
                res += 0.125 * dfs(r+x, c+y, l-1);
            }
            return res;
        };

        return dfs(row, column, k);
    }    
};