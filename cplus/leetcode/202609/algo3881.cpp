#include <bits/stdc++.h>
using namespace std;

// copy from math_template.cpp
const int MOD = 1e9 + 7;
const int MX = 1e5;   // 根据取值范围进行变更
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
// copy from math_template.cpp

class Solution {
public:
    int countVisiblePeople(int n, int pos, int k) {
        long long ans = 0;

        int l = pos, r = n - pos - 1;
        for (int i=max(0, k-r); i<=l && k-i<=r && k-i>=0; i++)  {
            ans += comb(l, i) * comb(r, k-i) * 2;
            ans %= MOD;
        }

        return ans;
    }
};