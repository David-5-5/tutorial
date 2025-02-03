#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 基础
class Solution {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        // 自行解答
        int mod = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> memo(m+1, vector<vector<int>>(n+1, vector<int>(17, -1)));

        function<int(int,int, int)> dfs = [&](int i, int j, int p) -> int {
        // auto dfs = [&](this auto&& dfs, int i, int j, int p) -> int {
            if (i >= m || j >= n) return 0;
            if (i == m-1 && j==n-1) {
                if ((p ^ grid[i][j]) == k) return 1;
                else return 0;
            }

            if (memo[i][j][p] != -1) return memo[i][j][p];

            int res = dfs(i+1, j, p ^ grid[i][j]);
            res += dfs(i, j+1, p^ grid[i][j]);

            return memo[i][j][p] = (res % mod);
        };

        return dfs(0,0,0);     

    }
};

int main() {
    vector<vector<int>> grid = {{2, 1, 5}, {7, 10, 0}, {12, 6, 4}};
    int k = 11;
    cout << Solution().countPathsWithXorValue(grid, k) << endl;
}