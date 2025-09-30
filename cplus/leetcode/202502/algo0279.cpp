#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  完全背包
class Solution {
public:
    int numSquares(int n) {
        // 将平方数加入数组
        vector<int> squares;
        for (int i=1; i<=sqrt(n); i++) {
            squares.push_back(i*i);
        }

        // 同 322
        vector<int> dp(n+1, -1);
        dp[0] = 0;
        for (auto& x : squares) {
            for (int k=x; k<=n; k++) {
                if (dp[k-x] == -1) continue;          // dp[k-x] is invalid
                if (dp[k] == -1) dp[k] = dp[k-x] + 1; // initial dp[k]
                else dp[k] = min(dp[k], dp[k-x]+1);   // set the minimize
            }
        }

        return dp[n];
    }


    int numSquares2(int n) {
        // 数学 拉格朗日四平方和定理：任何一个整数都可以被表示为至多四个正整数的平方和
        // 当 n != 4^k(8m+7) 时， n 可以被表示为至多三个整数的平方和
        // 当 n = 4^k(8m+7) 时， n 可以被表示为4个整数的平方和
        auto a = static_cast<int>(sqrt(n));
        if (a * a == n) return 1;

        auto val = n;
        while (val % 4 == 0) {
            val /= 4;
        }
        if ((val - 7)%8 == 0) return 4;

        // 两数的平方 参见 633
        a = 0;
        while (a * a * 2 <= n) {
            auto b = static_cast<int>(sqrt(n-a*a));
            if (a * a + b * b == n) return 2;
            a ++;
        }

        return 3;
    }


};