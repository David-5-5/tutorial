#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.2 二维差分
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        // 参考题意解答
        // 可作为二维前缀和及二维差分 模板
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> pres(n+1, vector<int>(m+1));
        vector<vector<int>> diff(n+1, vector<int>(m+1));

        // 计算 grid 二维前缀和
        for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) {
            pres[i+1][j+1] = grid[i][j] + pres[i+1][j] + pres[i][j+1] - pres[i][j];
        }

        // 遍历每个单元格，检查以每个单元格为左上角的，边长为stampHeight, stampWidth的矩形
        // 的前缀和是否为 0，即不存在被 1 占据的点
        // 若存在这样的点，则二维差分数组stampHeight, stampWidth的区间 +1
        for(int i=0; i+stampHeight-1<n; ++i) for(int j=0; j + stampWidth - 1<m; ++j) {
            int i1 = i + stampHeight - 1, j1 = j + stampWidth - 1;
            if (pres[i1+1][j1+1]-pres[i1+1][j]-pres[i][j1+1]+pres[i][j]==0) {
                diff[i][j] += 1;
                diff[i1+1][j] -= 1;
                diff[i][j1+1] -= 1;
                diff[i1+1][j1+1] = 1;
            }
        }

        // 计算diff的前缀和
        // vector<vector<int>> res(n+1, vector<int>(m+1));
        pres.assign(n+1, vector(m+1, 0));       // 复用pres空间，性能提升
        for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) {
            pres[i+1][j+1] = diff[i][j] + pres[i+1][j] + pres[i][j+1] - pres[i][j];
            if (pres[i+1][j+1] == 0 && grid[i][j]==0) return false;
        }
        return true;    
    }
};