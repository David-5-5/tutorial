#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector pre_r(m, vector<int>(n, 0)), pre_c(m, vector<int>(n, 0));
        for (int i=0; i<m; i++) pre_r[i][0] = grid[i][0];
        for (int i=0; i<n; i++) pre_c[0][i] = grid[0][i];

        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            if (grid[i][j]) {
                if (j) pre_r[i][j] = pre_r[i][j-1] + 1;
                if (i) pre_c[i][j] = pre_c[i-1][j] + 1;
            }
        }

        int ans = 0;
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            int side = min(pre_r[i][j], pre_c[i][j]);
            while (side > ans) {
                if (pre_r[i-side+1][j] >= side && pre_c[i][j-side+1]>=side) {
                    ans = side; break;
                }
                side --;
            }
        }            
        return ans * ans;
    }

    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector pre_r(m+1, vector<int>(n+1, 0)), pre_c(m+1, vector<int>(n+1, 0));
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            if (grid[i][j]) {
                pre_r[i+1][j+1] = pre_r[i+1][j] + 1;
                pre_c[i+1][j+1] = pre_c[i][j+1] + 1;
            }
        }

        int ans = 0;
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) {
            int side = min(pre_r[i+1][j+1], pre_c[i+1][j+1]);
            while (side > ans) {
                if (pre_r[i-side+2][j+1] >= side && pre_c[i+1][j-side+2]>=side) {
                    ans = side; break;
                }
                side --;
            }
        }            
        return ans * ans;
    }    
};