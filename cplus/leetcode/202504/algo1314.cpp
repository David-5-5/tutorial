#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  1.6 二维前缀和
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        // 自行解答
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

    vector<vector<int>> matrixBlockSum2(vector<vector<int>>& mat, int k) {
        // 自行解答 - 逐维前缀和
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> pres = mat;

        for (int i=1; i<n; ++i) for (int j=0; j<m; ++j) {
            pres[i][j] += pres[i-1][j];
        }
        for (int i=0; i<n; ++i) for (int j=1; j<m; ++j) {
            pres[i][j] += pres[i][j-1];
        }

        vector<vector<int>> ans(n, vector<int>(m));
        for (int i=0; i<n; ++i) for(int j=0; j<m; ++j) {
            int row1 = max(0, i-k), col1 = max(0, j-k);
            int row2 = min(n-1, i+k), col2 = min(m-1, j+k);

            ans[i][j] = pres[row2][col2] + (row1 && col1?pres[row1-1][col1-1]:0) -
                 (col1?pres[row2][col1-1]:0) - (row1?pres[row1-1][col2]:0);
        }        
        return ans;
    }    
};

int main() {
    vector<vector<int>> mat = {{1,2,3}, {4,5,6}, {7,8,9}};
    Solution().matrixBlockSum2(mat, 1);
}