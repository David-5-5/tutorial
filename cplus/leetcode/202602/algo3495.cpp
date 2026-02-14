#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        // 自行解答
        auto count = [](int l, int r) -> long long {
            long long mn = floor(log2(l)/2) + 1, mx = floor(log2(r)/2) + 1;
            long long n = 0;
            for (int i=mn; i<=mx; i++) {
                n += 1LL * (min((int)pow(4, i)-1, r) - max((int)pow(4,i-1), l) + 1) * i;
            }
            return max((n + 1)/2, mx);
        };

        long long ans = 0;
        for (auto & q: queries) ans += count(q[0], q[1]);

        return ans;    
    }


};