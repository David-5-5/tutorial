#include <bits/stdc++.h>
using namespace std;

// 复习
class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int ans = 0, cnt1 = 0, diff = 0;
        int m = grid.size(), n = grid[0].size();
        
        // 分类讨论：
        // 1. 对称的区域，上下左右对称的指必须相等，是 4 的倍数
        for (int i=0; i<m/2; i++) for (int j=0; j<n/2; j++) {
            int c1 = 0, c0 = 0;
            if (grid[i][j]) c1 ++; else c0++;
            if (grid[i][n-1-j]) c1++; else c0++;
            if (grid[m-1-i][j]) c1++; else c0++;
            if (grid[m-1-i][n-1-j]) c1++; else c0++;
            ans += min(c0, c1); // 最小的值就是修改的值
        }

        
        if (m % 2) {    // 2. 奇数行的中间行
            for (int j=0; j<n/2; j++) {
                if (grid[m/2][j] != grid[m/2][n-j-1]) diff++;   // 修改其中一个
                else cnt1 += 2 * grid[m/2][j];                  // 相同计算 1 的数量
            }
        }
        if (n % 2) {    // 3. 奇数列的中间列
            for (int i=0; i<m/2; i++) {
                if (grid[i][n/2] != grid[m-1-i][n/2]) diff++;   // 修改其中一个
                else cnt1 += 2 * grid[i][n/2];                  // 相同计算 1 的数量
            }
        }
        
        // 奇数行奇数列中间的唯一值必须为 0
        if ((m % 2) && (n % 2)) ans += 0 ^ grid[m/2][n/2]; 

        // 奇数行若相同的 1 的数量 = 2的情况，要看奇数行列中的修改树
        return ans + diff + (cnt1 % 4 == 2 && diff == 0?2:0);       
    }
};