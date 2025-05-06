#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  1.6 二维前缀和
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        // 参考题解，枚举
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> rows(m, vector<int>(n));

        // 按行统计 (i,j) 向左延伸的长度
        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) {
            if (mat[i][j]) 
                rows[i][j] = j?rows[i][j-1]+1:1;
            else rows[i][j] = 0;
        }

        int ans = 0;
        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) {
            int col = rows[i][j];
            // (i,j) 向上延伸的高度 k; 
            // 优化： 增加 col，当 col == 0 退出循环
            for (int k=i; k>=0&&col; k--) {   
                col = min(col, rows[k][j]);
                ans += col;
            }
        }
        return ans;  

    }
};