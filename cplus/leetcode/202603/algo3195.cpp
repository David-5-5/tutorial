#include <bits/stdc++.h>
using namespace std;

// 顺序做题
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        // 自行解答
        auto mininum = [&](int r1, int c1, int r2, int c2) -> int {
            int t_r = r2, b_r = 0, l_c = c2, r_c = 0;
            for (int r=r1; r<r2; r++) for (int c=c1; c<c2; c++) {
                if (grid[r][c] == 1) {
                    t_r = min(t_r, r); b_r = max(b_r, r);
                    l_c = min(l_c, c); r_c = max(r_c, c);
                }
            }

            if (t_r > b_r) return 0;
            else return (b_r - t_r + 1) * (r_c - l_c + 1);
        };

        return mininum(0, 0, grid.size(), grid[0].size());  
    }
};