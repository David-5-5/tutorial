#include <bits/stdc++.h>
using namespace std;


// 数学算法 - 组合数学 - 2.4 容斥原理
class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        // 自行解答 二分查找
        const int mod = 1e9 + 7;

        int c = lcm(a, b);
        auto check = [&] (long long mid) -> bool {
            return mid/a + mid/b - mid/c >= n;
        };
        long long left = min(a,b)-1, right = 1LL * c * n;

        while (left+1 < right) {
            long long mid = (right + left)/2;
            (check(mid)?right:left) = mid;
        }
        long long a_cnt = right/a, b_cnt = right/b, c_cnt=right/c;
        return max(a_cnt*a, max(b_cnt*b, c_cnt*c)) % mod;  
    }
};