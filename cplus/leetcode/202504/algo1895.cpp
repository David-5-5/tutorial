#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        // 自行解答 思维难度不高，但是代码写起来太复杂了
        int m = grid.size(), n = grid[0].size();
        // 对角线 前缀和
        vector<vector<int>> diag_down(n+m-1, vector<int>(m+1, 0)), diag_up(n+m-1, vector<int>(m+1, 0));
        // 行列 前缀和
        vector<vector<int>> rows(m, vector<int>(n+1, 0)), cols(m+1, vector<int>(n, 0));
        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) {
            diag_down[i-j+n-1][i+1] = diag_down[i-j+n-1][i] + grid[i][j];
            diag_up[i+j][i+1] = diag_up[i+j][i] + grid[i][j];
            rows[i][j+1] = rows[i][j] + grid[i][j];
            cols[i+1][j] = cols[i][j] + grid[i][j];
        }

        auto check = [&](int i1, int j1, int i, int j, int sum) -> bool{
            // check down diag
            if (diag_down[i-j+n-1][i+1] - diag_down[i-j+n-1][i1]!=sum) return false;
            // check up diag
            if (diag_up[i1+j][i+1] - diag_up[i1+j][i1]!=sum) return false;
            // check each row
            for (int r=i1; r<=i; r++) {
                if (rows[r][j+1]-rows[r][j1] != sum) return false;
            }
            // check each column
            for (int c=j1; c<=j; c++) {
                if (cols[i+1][c]-cols[i1][c] != sum) return false;
            }

            return true;
        };

        int ans = 1;
        for (int i = 1; i<m; ++i) for(int j=1; j<n; ++j) {
            for (int k=ans; k<=min(i,j); k++) {
                int i1 = i-k, j1 = j-k;
                int sum = rows[i][j+1] - rows[i][j1];
            
                if (check(i1, j1, i, j, sum)) {
                    ans = k+1;
                }
            }
        }
        return ans;
    }
};