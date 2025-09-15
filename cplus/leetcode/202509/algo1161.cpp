#include <bits/stdc++.h>
using namespace std;

// 二进制码转格雷码
uint32_t binaryToGray(uint32_t binary) {
    return binary ^ (binary >> 1);
}

// 格雷码转二进制码
uint32_t grayToBinary(uint32_t gray) {
    uint32_t binary = gray;
    // 从次高位开始处理，直到最低位
    while (gray >>= 1) {
        binary ^= gray;
    }
    return binary;
}

// 位运算 - 其他
class Solution {
public:
    int minimumOneBitOperations(int n) {
        return grayToBinary(n);
    }
};