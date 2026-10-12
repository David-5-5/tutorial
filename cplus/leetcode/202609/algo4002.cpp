#include <bits/stdc++.h>
using namespace std;

// comb 模板
/**
 * According to Fermat's theorem, if m is a prime number, 
 * we can compute x^{n mod (m-1)} to speed up the algorithm
 * 带模算的快速幂
 */
long long pow(long long base, int exp, int modulo)
{
    base %= modulo;
    long long res = 1;
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base % modulo;
        base = base * base % modulo;
        exp >>= 1;
    }
    return res;
}

const int MOD = 1e9 + 7;
const int MX = 5e5 + 1;   // 根据取值范围进行变更

long long fact[MX+1];
long long i_fact[MX+1];
auto init = [] {
    fact[0] = 1;
    for (int i=1; i<MX+1; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    i_fact[MX] = pow(fact[MX], MOD-2, MOD);
    for (int i=MX; i; i--) {
        i_fact[i-1] = i_fact[i] * i % MOD;
    }
    return 0;
}();

long long comb(int n, int m) {
    if (m > n) return 0;
    return (fact[n] * i_fact[m] % MOD) * i_fact[n-m] % MOD;
}
// comb 模板

class Solution {
public:
    int countValidSequences(int n, int k) {
        if (n <= k) return 0;
        
        if ((n%2) ^ (k%2)) return comb(n-1, k-1);
        else return (MOD + comb(n-1, k-1) - comb((n+k)/2-1, k-1)) % MOD;
    }
};

