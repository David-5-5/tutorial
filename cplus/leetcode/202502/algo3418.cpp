#include <bits/stdc++.h>
using namespace std;


// 动态规划 - 网格图 DP - 基础
class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        // 参考题解 
        // 开始思路有错，可以忽略两个负数，每个数作为参数，值为数值的取值范围-1~-1000
        // 题解的思路增加参数，记录忽略的参数，值的范围为 0，1，2，表示忽略负数的数量
        // 其他同 64 题。
        int m = coins.size(), n = coins[0].size();
        vector<vector<vector<int>>> memo(m, vector<vector<int>>(n, vector<int>(3, INT_MIN)));

        function<int(int,int, int)> dfs = [&](int i, int j, int p) -> int {
        // auto dfs = [&](this auto&& dfs, int i, int j, int p) -> int {
            if (i >= m || j >= n) return INT_MIN;
            if (i == m-1 && j==n-1) {
                return memo[i][j][p] = p<2 ? max(coins[i][j], 0) : coins[i][j];
            }

            if (memo[i][j][p] != INT_MIN) return memo[i][j][p];
            
            int& res = memo[i][j][p]; // 注意这里是引用
            res = max(dfs(i, j+1, p), dfs(i+1, j, p)) + coins[i][j];
            if (coins[i][j] < 0 && p<2) {
                res = max({res, dfs(i, j+1, p+1), dfs(i+1, j, p+1)});
            } 

            return res;
        };

        return dfs(0,0,0); 
    }
};