#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        // 朴素写法，可以通过增加变量，优化代码，合并四个方向的类似操作
        int m = grid.size(), n = grid[0].size();

        for (int i=0; i<min(m/2, n/2); i++) {
            vector<int> tmp;
            int x = i, y = i;
            for (; y<n-i-1; y++)  { // -->
                tmp.push_back(grid[x][y]);
            }
            for (; x<m-i-1; x++) {
                tmp.push_back(grid[x][y]);
            }
            for (; y>i; y--) {
                tmp.push_back(grid[x][y]);
            }
            for (; x>i; x--) {
                tmp.push_back(grid[x][y]);
            }
            int ptr = k % tmp.size();
            x = i; y = i;
            for (; y<n-i-1; y++)  { // -->
                grid[x][y] = tmp[ptr++]; ptr %= tmp.size();
            }
            for (; x<m-i-1; x++) {
                grid[x][y] = tmp[ptr++]; ptr %= tmp.size();
            }
            for (; y>i; y--) {
                grid[x][y] = tmp[ptr++]; ptr %= tmp.size();
            }
            for (; x>i; x--) {
                grid[x][y] = tmp[ptr++]; ptr %= tmp.size();
            }            
        }

        return grid;        
    }
};