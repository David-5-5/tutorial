#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int numOfWays(int n) {
        // 自行解答，数学方法
        // 起初两种颜色方案 6 种，三种颜色方案是 6
        // 两种颜色的方案的下一行是 5 种方案，col2 * 5，其中 col2 * 3 是两种颜色，col2 * 2 是三种颜色
        // 三种种颜色的方案的下一行是 4 种方案，col3 * 4，其中 col3 * 2 是两种颜色，col3 * 2 是三种颜色
        const int mod = 1e9 + 7;
        int col2 = 6, col3 = 6;
        for (int _=0; _<n-1; _++) {
            int new_col2 = ((long)col2 * 3 + col3 * 2) % mod;
            int new_col3 = ((long)col2 * 2 + col3 * 2) % mod;
            col2 = new_col2, col3 = new_col3;
        }

        return ((long)col2 + col3) % mod;
    }
};