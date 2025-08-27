#include <bits/stdc++.h>
using namespace std;

// 位运算 - 与或（AND/OR）的性质
class Solution {
public:
    long long minEnd(int n, int x) {
        // 自行解答 比题解写的还简洁!!!
        long long ans = x; int i = 0; n--;   // 从 0 开始计数
        while (n) {
            if (((ans >> i) & 1) == 0) { // 如果当前位是1，那么我们需要将ans的对应位也设置为1
                ans |= ((long)(n&1) << i);
                n >>= 1; // 右移一位，处理下一位
            }
            i++;
        }
        return ans;
    }
};