#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        // 累了，直接看的参考题解，
        // 二维数组的前缀和快速判断
        const int MOD = 1e9 + 7;
        int m = pizza.size(), n = pizza[0].length();

        // check whether or not matrix (x1, y1, x2, y2) include apple
        auto check = [&](int x1, int y1, int x2, int y2) -> bool {
            return false;
        };

        auto dfs = [&](this auto&& dfs, int c, int i, int j) -> int {
            if (c == 0) // 递归边界：无法再切了
            return check(i, j, m, n) ? 1 : 0;

        };
    }
};