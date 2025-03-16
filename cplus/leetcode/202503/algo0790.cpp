#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  矩阵快速幂优化 DP
class Solution {
public:
    int numTilings(int n) {
        // 参考题解
        // 状态转移方程 dp(n) = 2 * dp(n-1) + f(n-3)
        // f1 = 1, f2 = 2; f3 = 5
        const int mod = (1e9+7);
        int f1 = 1, f2 = 2, f3 = 5;
        if (n == 1) return f1;
        if (n == 2) return f2;
        if (n == 3) return f3;

        while (n>=4) {
            int nxt = ((long) 2 * f3 + f1) % mod;
            // cout << nxt << endl;
            f1 = f2, f2 = f3, f3 = nxt;
            n --;
        }

        return f3;    
        
    }
};