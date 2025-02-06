#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 网格图 DP - 进阶
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        // 自行解答
        int m = grid.size(), n = grid[0].size();

        if ((m + n - 1)%2 || grid[0][0] == ')' || grid[m-1][n-1] == '(') return false;

        vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>((m+n-1/2 + 1), -1)));

        function<bool(int,int,int)> dfs = [&](int i, int j, int p) -> bool {
            
            if (i>=m || j>=n || p > (m+n-1)/2 || p < 0) {
                return false;
            }            
            if (i == m-1 && j == n-1) if (p == 1) return true; else return false;

            if (memo[i][j][p] != -1) return memo[i][j][p];

            // p 的下一个值放到递归函数内部
            int change = grid[i][j] == '(' ? 1 : -1;
            if (dfs(i+1, j, p + change)) return memo[i][j][p] = 1;
            if (dfs(i, j+1, p + change)) return memo[i][j][p] = 1;

            return memo[i][j][p] = 0;
        };

        return dfs(0,0,0);
    }
};