#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // 数学 k 进制
        int k = minutesToTest / minutesToDie  + 1;

        return  ceil(log(buckets) / log(k) - 1e-5);
    }
};