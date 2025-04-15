#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 1.5 其他一维前缀和
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        // 自行解答，思维难度不高，但是代码写起来太复杂了太费时了
        int m = grid.size(), n = grid[0].size();
        set<int, greater<int>> values;      // 倒序排列

        vector<vector<int>> diag_down(n+m-1, vector<int>(m+1, 0)), diag_up(n+m-1, vector<int>(m+1, 0));
        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) {
            // 计算 对角线 前缀和 模板
            // down：i - j = [-(m-1),(n-1)], up i+j = k
            // 主对角线的特点 i-j = [-(n-1),(m-1)]，因此加上偏移量 n-1
            // 副对角线的特点 i+j = [0, m+n-1] 
            // 因此主副都有m+n-1条对角线，按行计算前缀和
            diag_down[i-j+n-1][i+1] = diag_down[i-j+n-1][i] + grid[i][j];
            diag_up[i+j][i+1] = diag_up[i+j][i] + grid[i][j];
            values.insert(grid[i][j]);      // 这句话不在模板内
        }

        for (int i = 0; i<m; ++i) for(int j=0; j<n; ++j) { // 遍历每个顶点作为菱形的top
            for (int l=1; l<min(n, m); l++) {   // 长度从 1 遍历，长度为 0 即点本身
                int left_i = i + l, left_j = j - l, right_i = i + l, right_j = j + l;
                int bottom_i = i + 2 * l, bottom_j = j;
                if (bottom_i<m && left_j>=0 && right_j<n) { // 菱形顶点都在矩阵内 - 合法
                    int res = diag_down[i-j+n-1][right_i+1] - diag_down[i-j+n-1][i];
                    res += diag_up[i+j][left_i+1] - diag_up[i+j][i];
                    res += diag_down[left_i-left_j+n-1][bottom_i+1] - diag_down[left_i-left_j+n-1][left_i];
                    res += diag_up[right_i+right_j][bottom_i+1] - diag_up[right_i+right_j][right_i];
                    // 四个顶点重复计算，减去即可
                    res -= grid[i][j] + grid[left_i][left_j] + grid[right_i][right_j] + grid[bottom_i][bottom_j];
                    values.insert(res);
                } else break;   // 不合法退出
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