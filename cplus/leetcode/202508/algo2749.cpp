#include <bits/stdc++.h>
using namespace std;

// 位运算 - 思维题 - 贪心、脑筋急转弯等
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        // 自行解答
        int cnt = 0;
        long long val = num1;
        while (val > num2) {
            cnt ++;
            val -= num2;
            // int long 的方法不一致
            auto bitCount = __builtin_popcountll(val);
            // 2^i >= 1 因此 9 支持 4 + 4 + 1 cnt = 3, 但是 1 不支持 1 + 0 cnt = 2
            if (bitCount <= cnt) return val>cnt-bitCount?cnt:-1;
        }

        return -1;   
    }
};