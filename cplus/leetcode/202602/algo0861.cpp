#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        // 自行解答
        int m = grid.size(), n = grid[0].size();
        // 第一列全为 1，每行按照第一列进行移动，保证第1列为 1
        int ans = (1 << (n-1)) * m;
        
        for (int c=1; c<n; c++) {
            int ones = 0;
            for (int r=0; r<m; r++) 
                // 与第一列相同的就是 1
                if (grid[r][c] == grid[r][0]) ones ++;
            ans += (1<<(n-c-1)) * max(ones, m-ones);    // 每列取1或0数量的最大值
        }
        return ans;  
    }
};