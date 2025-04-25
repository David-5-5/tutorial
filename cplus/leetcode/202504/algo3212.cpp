#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        vector<vector<int>> prex(m+1, vector<int>(n+1)); // count x
        vector<vector<int>> pres(m+1, vector<int>(n+1)); // sum of X：1, Y:-1 .:0
        int ans = 0;
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            char cur = grid[i][j];
            pres[i+1][j+1] = (cur=='X'?1:(cur=='Y'?-1:0)) + pres[i][j+1] + pres[i+1][j] - pres[i][j];
            prex[i+1][j+1] = (cur=='X'?1:0) + prex[i][j+1] + prex[i+1][j] - prex[i][j];
            if (pres[i+1][j+1] == 0 && prex[i+1][j+1]) ans ++;
        }
        return ans;
    }
};