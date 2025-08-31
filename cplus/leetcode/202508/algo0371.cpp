#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int getSum(int a, int b) {
        // 参考题解
        // 按位进行相加
        // 0 + 0 = 0
        // 1 + 0 = 1        // a ^ b 异或结果 
        // 1 + 0 = 1        // a ^ b 异或结果
        // 1 + 1 = 0 (进位)  // (a & b) << 1 与 及 移位操作
        while (b) {
            // a 与 b 相同的位需要移位，不同的位相当于异或
            int carry = (a & b) << 1, _xor = a ^ b;
            a = carry | _xor;
            b = carry & _xor;   // 准备下次
        }
        return a;
    }
};