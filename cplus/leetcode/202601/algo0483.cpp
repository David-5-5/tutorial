#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    string smallestGoodBase(string n) {
        // 参考题解 数学公式推导
        // n = k^0 + k^1 + ... + k^m = (k^(m+1) - 1) / (k-1) 
        // 确定 m 的最大值及 k < n^(1/m)枚举 m 及 k
        long long nval = stol(n);
        int mMax = floor(log(nval)/log(2));
        for (int m = mMax; m>1; m--) {
            int k = pow(nval, 1.0/ m);
            long long mul = 1, sum =1;
            for (int i=0; i<m; i++) {
                mul *= k; sum += mul;
            }
            if (sum == nval) return to_string(k);
        }

        return to_string(nval - 1);
    }
};