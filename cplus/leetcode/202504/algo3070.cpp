#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  1.6 二维前缀和
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> pres(n+1, vector<int>(m+1));

        for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) {
            pres[i+1][j+1] = grid[i][j] + pres[i][j+1] + pres[i+1][j] - pres[i][j];
        }

        int ans = 0;
        for (int i=0; i<n; ++i) for(int j=0; j<m; ++j) {           
            if (pres[i+1][j+1] - pres[i+1][0] - pres[0][j+1] <= k)
                ans += 1;
        }        
        
        return ans;
    }
};