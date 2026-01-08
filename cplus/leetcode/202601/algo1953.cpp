#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.7 其他
class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        // Sn = ∑∑ |x| + |y| = 2n(n+1)(2n+1)
        int n = 0;
        long long sum = 0;
        while (sum < neededApples) {
            n ++;
            sum = 2LL * n * (n+1) * (2 * n + 1);
        }

        return n * 8;
        
    }
};
