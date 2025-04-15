#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<int, greater<int>> values;

        vector<vector<int>> diag_down(n+m-1, vector<int>(m+1, 0)), diag_up(n+m-1, vector<int>(m+1, 0));
        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) {
            // down：i - j = [-(m-1),(n-1)], up i+j = k
            diag_down[i-j+n-1][i+1] = diag_down[i-j+n-1][i] + grid[i][j];
            diag_up[i+j][i+1] = diag_up[i+j][i] + grid[i][j];
            values.insert(grid[i][j]);
        }

        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) { // 遍历每个顶点作为菱形的top
            for (int l=1; l<min(n, m); l++) {
                int left_i = i + l, left_j = j - l, right_i = i + l, right_j = j + l;
                int bottom_i = i + 2 * l, bottom_j = j;
                if (bottom_i<m && left_j>=0 && right_j<n) { // 矩形合法
                    int res = diag_down[i-j+n-1][right_i+1] - diag_down[i-j+n-1][i];
                    res += diag_up[i+j][left_i+1] - diag_up[i+j][i];
                    res += diag_down[left_i-left_j+n-1][bottom_i+1] - diag_down[left_i-left_j+n-1][left_i];
                    res += diag_up[right_i+right_j][bottom_i+1] - diag_up[right_i+right_j][right_i];
                    res -= grid[i][j] + grid[left_i][left_j] + grid[right_i][right_j] + grid[bottom_i][bottom_j];
                    values.insert(res);
                } else break;
            }
        }
        
        vector<int> ans;
        int count = 0;
        for (auto & v : values) {
            if (count++ >= 3) break;
            ans.push_back(v);
        }
        
        return ans;
    }
};