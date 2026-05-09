#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.5 贡献法
class Solution {
public:
    const int MOD = 1e9 + 7;
    // Fast exponentiation (Fast exponentiation)
    long long qpow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    // translate from python
    int sumOfNumbers(int l, int r, int k) {
        long long inv9 = qpow(9, MOD - 2);
        long long n = r - l + 1;
        long long sum_lr = (l + r) % MOD * n % MOD * qpow(2, MOD - 2) % MOD;
        
        long long ans = qpow(n, k - 1) * sum_lr % MOD;
        ans = ans * ((qpow(10, k) - 1 + MOD) % MOD) % MOD;
        ans = ans * inv9 % MOD;
        
        return ans;
    }
};