#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 中位数贪心
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        // 自行解答，中位数贪心
        int n =grid.size(), m = grid[0].size();

        int rem = grid[0][0] % x;   // 所有数同余，取第一个元素作为基准
        vector<int> quoients;

        for (int r=0; r < n; r++) {
            for (int c=0; c < m; c++) {
                if (grid[r][c] % x != rem) return -1;
                quoients.push_back(grid[r][c] / x);  // 计算商
            }
        }
        sort(quoients.begin(), quoients.end()); // 商排序
        int mid = m*n / 2; // quoients[mid] 为商的中位数
        int ans = 0;
        for (auto v :quoients) {
            ans += abs(v-quoients[mid]);
        }

        return ans;

    }
};