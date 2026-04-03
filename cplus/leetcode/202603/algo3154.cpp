#include <bits/stdc++.h>
using namespace std;

// 适合较小的组合数，若 n 较大，容易爆 long long
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    k = min(k, n - k);
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - k + i) / i;
    }
    return res;
}

class Solution {
public:
    int waysToReachStair(int k) {
        // 复习 
        long long ans = 0;
        for (int j = 0; j < 32; ++j) {
            long long i = 1LL << j; // 2^j
            int m = i - k;
            if (m >= 0 && m <= j + 1) {
                ans += comb(j + 1, m);
            } else if (m > k + 1) {
                break;
            }
        }
        return (int)ans;
    }
};

