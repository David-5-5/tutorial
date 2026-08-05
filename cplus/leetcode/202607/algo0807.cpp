#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size(); vector<int> row_mx(n), col_mx(n);
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
            row_mx[i] = max(row_mx[i], grid[i][j]);
            col_mx[j] = max(col_mx[j], grid[i][j]);
        }
        int ans = 0;
        for (int i=0; i<n; i++) for (int j=0; j<n; j++) {
            ans += min(row_mx[i], col_mx[j]) - grid[i][j];
        }
        return ans;

    }
};