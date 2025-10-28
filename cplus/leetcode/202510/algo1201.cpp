#include <bits/stdc++.h>
using namespace std;


// 数学算法 - 组合数学 - 2.4 容斥原理
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        // 自行解答 二分查找
        auto _lcm = [](long long a, long long b) -> long long {
            return lcm(a, b);
        };
        long long ab = _lcm(a, b), bc = _lcm(b,c), ac = _lcm(a, c), abc = _lcm(a, bc);
        // long long ab = lcm(1LL*a, 1LL*b), bc = lcm(1LL*b,1LL*c), ac = lcm(1LL*a,1LL*c), abc = lcm(1LL*a, bc);
        auto check = [&] (long long mid) -> bool {
            return mid/a + mid/b + mid/c - mid/ab - mid/bc - mid/ac + mid/abc  >= n;
        };
        // 精确的选择 right 处理整数越界很棘手
        long long left = min(a,min(b,c))-1, right = 1LL*max(a,max(b,c))*n;

        while (left+1 < right) {
            long long mid = (right + left)/2;
            (check(mid)?right:left) = mid;
        }
        long long a_cnt = right/a, b_cnt = right/b, c_cnt=right/c, 
            ab_cnt = right/ab, bc_cnt = right/bc, 
            ac_cnt = right/ac, abc_cnt = right/abc;
        return max({a_cnt*a, b_cnt*b, c_cnt*c, ab_cnt*ab, bc_cnt*bc, ac_cnt*ac, abc_cnt*abc});
    }
};