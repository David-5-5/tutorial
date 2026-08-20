#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        int ans = 0;

        for (int i=0; i<m-2; i++) for (int j=0; j<n-2; j++) {
            if (grid[i+1][j+1] != 5) continue;
            
            vector<int> sum_r(3), sum_c(3); int mask = 0;
            for (int r=i; r<3+i; r++) for (int c=j; c<3+j; c++) {
                sum_r[r-i] += grid[r][c]; sum_c[c-j] += grid[r][c];
                mask |= 1 << grid[r][c];
            }

            if (mask == 1022 && sum_r[0] == 15 && sum_r[1] == 15
                && sum_c[0] == 15 && sum_c[1] == 15) ans ++;
        }
        
        return ans;
    }
};