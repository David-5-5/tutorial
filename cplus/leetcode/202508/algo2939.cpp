#include <bits/stdc++.h>
using namespace std;

// 位运算 - 思维题 - 贪心、脑筋急转弯等
class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        // 复习
        const int mod = 1e9 + 7; bool isFirst = true;   // 不同的最高位设置为 a
        if (a < b) swap(a, b);
        long long mx_mask = (1L << n)-1;
        if (a > mx_mask && (a & ~mx_mask) != (b & ~mx_mask)) {
            isFirst = false;
        }

        for (int i=n-1; i>=0; i--) {
            if (((a >> i) & 1) == ((b >> i) & 1)) {
                a |= 1L << i; b |= 1L << i;
            } else {
                if (isFirst) {a |= 1L << i; b &= ~(1L << i); isFirst = false;}
                else {b |= 1L << i; a &= ~(1L << i);}
            }
        }

        return (a % mod) * (b % mod) % mod;    
    }
};