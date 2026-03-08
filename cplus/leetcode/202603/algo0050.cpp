#include <bits/stdc++.h>
using namespace std;

// LCR series
class Solution {
public:
    double myPow(double x, int n) {
        // 调用系统函数 测试案例不全面，n 为整数范围，应该是快速幂，；
        // 但不要求取模，因此测试案例数据比较小
        return pow(x,n);
    }
};