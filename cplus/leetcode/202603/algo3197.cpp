#include <bits/stdc++.h>
using namespace std;

// 顺序做题
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        // 参考解题思路
        // 分为三个区域，六种区域划分 :
        // ||   -|   |- , 将以上三种旋转 90
        
        auto calc = [] (vector<vector<int>>& matrix) -> int {
            int ans = INT_MAX;
            auto mininum = [&](int r1, int c1, int r2, int c2) -> int {
                int t_r = r2, b_r = 0, l_c = c2, r_c = 0;
                for (int r=r1; r<r2; r++) for (int c=c1; c<c2; c++) {
                    if (matrix[r][c] == 1) {
                        t_r = min(t_r, r); b_r = max(b_r, r);
                        l_c = min(l_c, c); r_c = max(r_c, c);
                    }
                }

                if (t_r > b_r) return 0;
                else return (b_r - t_r + 1) * (r_c - l_c + 1);
            };            
            int end_r = matrix.size(), end_c = matrix[0].size();
            for (int c1=1; c1<end_c-1; c1++) for (int c2=c1+1; c2<end_c; c2++) {
                ans = min(ans, mininum(0, 0, end_r, c1) + mininum(0, c1, end_r, c2) + mininum(0, c2, end_r, end_c));
            }
            for (int c=1; c<end_c; c++) for (int r=1; r<end_r; r++) {
                ans = min(ans, mininum(0, 0, end_r, c) + mininum(0, c, r, end_c) + mininum(r, c, end_r, end_c));
            }
            for (int r=1; r<end_r; r++) for (int c=1; c<end_c; c++)  {
                ans = min(ans, mininum(0, 0, r, c) + mininum(r, 0, end_r, c) + mininum(0, c, end_r, end_c));
            }
            return ans;
        };

        int res1 = calc(grid);

        vector totate(grid[0].size(), vector<int>(grid.size()));
        for (int r=0; r<grid.size(); ++r) for (int c=0; c<grid[0].size(); ++c)
            totate[c][r] = grid[r][c];

        return min(res1, calc(totate));     

    }
};