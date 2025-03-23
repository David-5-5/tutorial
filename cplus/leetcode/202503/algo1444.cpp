#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        // 累了，直接看的参考题解，
        // 二维数组的前缀和快速判断
        const int MOD = 1e9 + 7;
        int m = pizza.size(), n = pizza[0].length();

        // TEMPLATE BEGIN 二维前缀和/矩阵前缀和 
        vector<vector<int>> pres(m+1, vector<int>(n+1));
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                pres[i+1][j+1] = (pizza[i][j]&1) + pres[i+1][j] + pres[i][j+1] - pres[i][j];
            }
        }
        // TEMPLATE END 二维前缀和/矩阵前缀和 模板

        // TEMPLATE BEGIN - CALCULATE SUM OF SUB-MATRIX 
        // check whether or not matrix (x1, y1, x2, y2) include apple
        auto check = [&](int x1, int y1, int x2, int y2) -> bool {
            return pres[x2][y2] + pres[x1][y1] - pres[x1][y2] - pres[x2][y1];
        };
        // TEMPLATE END - CALCULATE SUM OF SUB-MATRIX 

        vector<vector<vector<int>>> memo(k, vector<vector<int>>(m, vector<int>(n, -1)));
        auto dfs = [&](this auto&& dfs, int c, int i, int j) -> int {
            if (c == 0) // 递归边界：无法再切了
                return check(i, j, m, n) ? 1 : 0;
            
            auto& res = memo[c][i][j];

            if (res != -1) return res;
            
            res = 0;
            for (int j2=j+1; j2<n; j2++) {  // 垂直切
                if (check(i, j, m, j2)) {
                    res = (res + dfs(c-1, i, j2)) % MOD;
                }
            }
            
            for (int i2=i+1; i2<m; i2++) {  // 水平切
                if (check(i, j, i2, n)) {
                    res = (res + dfs(c-1, i2, j)) % MOD;
                }
            }
            return res;
        };
        return dfs(k-1, 0, 0);
    }
};