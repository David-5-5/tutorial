#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.1 回文数
class Solution {
public:
    int largestPalindrome(int n) {
        // 参考题解，枚举回文数的右半部分从 10^n - 1 开始，回文数为 p
        // 枚举 n 的整数 x 从 10 ^n -1 开始到 sqrt(P)
        // 时间复杂度为 O(10^(2*N)) 看着很大实际很小
        
        if (n == 1) return 9;

        int upper = pow(10, n) - 1;
        for (int left=upper; left > 0; left --) {
            long long p = left, x = left;
            while (x) {
                p = p * 10 + x % 10; x /= 10;
            }

            // 关键点 x * x >= p 是时间复杂度及正确性的保证
            for (int x=upper; 1LL * x * x >= p; x--) {
                if (p % x == 0) {
                    return p % 1337;
                }
            }
        }
        return -1;
    }
};