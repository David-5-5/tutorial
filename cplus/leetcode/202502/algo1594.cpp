#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 进阶
class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        // 参考题解，使用 64 作为模板
        int mod = 1e9 + 7;

        int m = grid.size(), n = grid[0].size();
        vector<vector<long>> maxf(m, vector<long>(n));
        vector<vector<long>> minf(m, vector<long>(n));

        maxf[0][0] = minf [0][0] = grid[0][0];
        for (int i=1; i<m; i++) maxf[i][0] = minf[i][0] = maxf[i-1][0] * grid[i][0];
        for (int i=1; i<n; i++) maxf[0][i] = minf[0][i] = maxf[0][i-1] * grid[0][i];

        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                int x = grid[i][j];
                if (x >= 0) {
                    maxf[i][j] = max(maxf[i-1][j],maxf[i][j-1]) * x;
                    minf[i][j] = min(minf[i-1][j],minf[i][j-1]) * x;
                } else {
                    maxf[i][j] = min(minf[i-1][j],minf[i][j-1]) * x;
                    minf[i][j] = max(maxf[i-1][j],maxf[i][j-1]) * x;
                }
            }
        }

        if (maxf[m-1][n-1] < 0) return -1;
        else return  maxf[m-1][n-1];  
    }
};