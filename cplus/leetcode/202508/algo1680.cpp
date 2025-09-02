#include <bits/stdc++.h>
using namespace std;

// 位运算 - 其他
class Solution {
public:
    int concatenatedBinary(int n) {
        // 自行解答
        const int mod =  1e9 + 7;
        
        auto bit_length = [](int val) -> int {
            int len = 0;
            while (val) {
                val >>= 1; len++;
            }
            return len;
        };

        long  long ans = 1;
        for (int i = 2; i<=n; ++i) {
            ans <<= bit_length(i);
            ans = (ans + i) % mod;
        }
        return ans;    
    }


    int concatenatedBinary(int n) {
        // 参考题解 使用 bit_width
        const int mod =  1e9 + 7;

        long  long ans = 1;
        for (int i = 2; i<=n; ++i) {
            ans <<= bit_width((unsigned) i);
            ans = (ans + i) % mod;
        }
        return ans;    
    }    
};