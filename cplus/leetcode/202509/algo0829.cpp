#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.5 因子
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int ans = 1;
        auto tri = [](int r) -> int {
            return (1 + r) * r / 2;
        };

        // 最小的前缀和 (i+1)*i / 2 等于 n 确定的最大 i 为循环边界
        for (int i = 2; (i*i+i)<=2*n; ++i) {
            if ((n - tri(i-1)) % i == 0) ans ++;
        }

        return ans;
    }
};