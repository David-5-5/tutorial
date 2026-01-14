#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    long long lastInteger(long long n) {
        long long start = 1, d = 1;

        while (n > 1) {
            // start += (n - 1 - (n+1) % 2) * d;
            start += (n-2 + n % 2) * d;
            d *= -2;
            n = (n + 1) / 2;
        }

        return start;
    }
};