#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.2 整数拆分
class Solution {
public:
    int integerBreak(int n) {
        // 自行解答
        int ans = 1;
        for (int k=2; k<=n; ++k) {
            int frac = n / k, rem = n % k;
            int res = 1;
            for (int _=0; _<rem; ++_) res *= (frac+1);
            for (int _=0; _<k-rem; ++_) res *= frac;
            if (res <= ans) break;
            else ans = res;
        }
        return ans;
    }
};