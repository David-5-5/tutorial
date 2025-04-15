#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> pre_row_2(m, vector<int>(n+1));
        vector<vector<int>> pre_row_5(m, vector<int>(n+1));
        vector<vector<int>> pre_col_2(n, vector<int>(m+1));
        vector<vector<int>> pre_col_5(n, vector<int>(m+1));

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
            pre_col_5[i+1][j] = pre_col_5[i][j] + cnt_2;

        }


    }
};