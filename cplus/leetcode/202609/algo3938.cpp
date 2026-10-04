#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int ans = INT_MIN/2, m = grid.size(), n = grid[0].size();

        for (int i=0; i<m; i++) {
            auto f = grid[i][0];                // 这三行简单代码，太厉害了，       （1）
            for (int j=1; j<n; j++) {
                ans = max(ans, f + grid[i][j]); // f + grid[i][j] 至少包含两个数   （2）
                f = max(f, 0) + grid[i][j];     //                                （3）  
            }
        }
        for (int j=0; j<n; j++) {
            auto f = grid[0][j];
            for (int i=1; i<m; i++) {
                ans = max(ans, f + grid[i][j]);
                f = max(f, 0) + grid[i][j];
            }
        } 
        for (int i=1; i<m-1; i++) for (int j=1; j<n-1; j++) {
            ans = max(ans, grid[i][j]);
        }
        return ans;
    }
};