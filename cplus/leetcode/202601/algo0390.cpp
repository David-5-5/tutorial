#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int lastRemaining(int n) {
        // 自行解答， 同3782
        long long start = 1, d = 1;

        while (n > 1) {
            start += (n - 1 - n  % 2) * d;
            d *= -2;
            n /= 2;
        }

        return start;    
    }
};