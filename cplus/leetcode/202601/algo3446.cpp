#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 零、常用枚举技巧 - 0.3 遍历对角线
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size(); vector<int> arr;
        // 上三角对角线
        for (int c=n-2; c>0; c--) {
            int m = n - c; arr.clear();
            for (int r = 0; r<m; r++) {
                arr.push_back(grid[r][c+r]);
            }
            sort(arr.begin(), arr.end());
            for (int r = 0; r<m; r++) {
                grid[r][c+r] = arr[r];
            }
        }
        // 下三角对角线
        for (int r=0; r<n-1; r++) {
            int m = n - r; arr.clear();
            for (int c = 0; c<m; c++) {
                arr.push_back(grid[r+c][c]);
            }
            sort(arr.rbegin(), arr.rend());
            for (int c = 0; c<m; c++) {
                grid[r+c][c] = arr[c];
            }
        }
        return grid;    
    }
};