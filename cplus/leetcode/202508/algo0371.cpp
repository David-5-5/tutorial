#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int getSum(int a, int b) {
        while (b) {
            // a 与 b 相同的位需要移位，不同的位相当于异或
            int carry = (a & b) << 1, _xor = a ^ b;
            a = carry | _xor;
            b = carry & _xor;   // 准备下次的
        }
        return a;
    }
};