#include <bits/stdc++.h>
using namespace std;

// 同 304
class NumMatrix {
private:
    vector<vector<int>> pres;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        // 自行解答 二维数组前缀和 模板
        int n = matrix.size(), m = matrix[0].size();

        pres.assign(n+1, vector<int>(m+1));
        for (int i=0; i<n; ++i) for (int j=0; j<m; ++j) {
            pres[i+1][j+1] = matrix[i][j] + pres[i][j+1] + pres[i+1][j] - pres[i][j];
        }

    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return pres[row2+1][col2+1] + pres[row1][col1]- pres[row2+1][col1] - pres[row1][col2+1];
    }
};
