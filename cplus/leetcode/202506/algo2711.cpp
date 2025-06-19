#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 前后缀分解
class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        // 主对角线的上的上下两部分的不同值的数量，直接暴力吧
        int m = grid.size(), n = grid[0].size();

        vector ans(m, vector<int>(n));

        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) {
            set<int> top;
            int x = i-1, y = j-1;
            while (x>=0 && y >=0) {
                top.insert(grid[x][y]);
                x --; y --;
            }
            set<int> bottom;
            x = i+1, y = j+1;
            while (x<m && y <n) {
                bottom.insert(grid[x][y]);
                x ++; y ++;
            }

            ans[i][j] = abs((int)top.size()-(int)bottom.size());
            
        }
        return ans;
    }
};