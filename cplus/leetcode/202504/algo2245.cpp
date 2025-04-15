#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> pre_row_2(m, vector<int>(n+1));
        vector<vector<int>> pre_row_5(m, vector<int>(n+1));
        vector<vector<int>> pre_col_2(m+1, vector<int>(n));
        vector<vector<int>> pre_col_5(m+1, vector<int>(n));

        for (int i=0; i<m; i++) for (int j=0; j<n; ++j) {
            int val = grid[i][j], cnt_2 = 0, cnt_5 = 0;
            while (val % 5 == 0) {
                cnt_5 ++;
                val /= 5;
            }
            while (val % 2 == 0) {
                cnt_2 ++;
                val /= 2;
            }
            pre_row_2[i][j+1] = pre_row_2[i][j] + cnt_2;
            pre_row_5[i][j+1] = pre_row_5[i][j] + cnt_5;

            pre_col_2[i+1][j] = pre_col_2[i][j] + cnt_2;
            pre_col_5[i+1][j] = pre_col_5[i][j] + cnt_5;

        }

        int ans = 0;
        for (int i=0; i<m; i++) for (int j=0; j<n; ++j) {
            int row_2_left = pre_row_2[i][j+1], row_5_left = pre_row_5[i][j+1];
            int row_2_right = pre_row_2[i][n] - pre_row_2[i][j], 
                    row_5_right = pre_row_5[i][n] - pre_row_5[i][j];
            
            int col_2_up = pre_col_2[i][j], col_5_up = pre_col_5[i][j];
            int col_2_down = pre_col_2[m][j] - pre_col_2[i+1][j], 
                    col_5_down = pre_col_5[m][j] - pre_col_5[i+1][j];
                    
            ans = max(ans, min(row_2_left + col_2_up, row_5_left + col_5_up));
            ans = max(ans, min(row_2_left + col_2_down, row_5_left + col_5_down));
            ans = max(ans, min(row_2_right + col_2_up, row_5_right + col_5_up));
            ans = max(ans, min(row_2_right + col_2_down, row_5_right + col_5_down));
        }
        return ans;
    }
};