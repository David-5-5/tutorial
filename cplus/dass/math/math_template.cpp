#include <iostream>
using namespace std;

/**
 * Binary exponentiation, is a trick to calculate a^n in the time of O(logN),
 * while the calculation of brute force takes the time of O(N).
 * 快速幂
 */
long long pow(long long base, int exp)
{
    long long res = 1;
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

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

/**
 * 组合数计算，使用逆元，打表 代替系统的 comb 函数
 * comb(n, m) = n! / m! * (n-m)!    n >= m
 */

const int MOD = 1e9 + 7;
const int MX = 1e5;   // 根据取值范围进行变更

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




int main()
{
    cout << " 23 ^ 102222 = " << pow(23, 1000222) << endl;
    cout << " 23 ^ 102222 % 2345 = " << pow(23, 1000222, 2345) << endl;
}
