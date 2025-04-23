#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  1.6 二维前缀和
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> pres(n+1, vector<int>(m+1));

        for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) {
            pres[i+1][j+1] = mat[i][j] + pres[i][j+1] + pres[i+1][j] - pres[i][j];
        }

        vector<vector<int>> ans(n, vector<int>(m));
        for (int i=0; i<n; ++i) for(int j=0; j<m; ++j) {
            int row1 = max(0, i-k), col1 = max(0, j-k);
            int row2 = min(n-1, i+k), col2 = min(m-1, j+k);

            ans[i][j] = pres[row2+1][col2+1] + pres[row1][col1] - pres[row2+1][col1] - pres[row1][col2+1];
        }
        
        return ans;    
    }
};