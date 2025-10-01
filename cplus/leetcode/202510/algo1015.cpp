#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.10 其他
class Solution {
    // 计算欧拉函数，即 n 以内与 n 互质的数的个数
    int phi(int n) {
        int res = n;
        for (int i=2; i*i<=n; ++i) {
            if (n % i == 0) {
                res = res / i * (i-1);
                while (n%i==0) n/=i;
            }
        }
        if (n>1) res = res/n * (n-1);   // n 是质数
        return res;
    }

    long long pow(long long x, int n, long long mod) {
        int ans = 1; x %= mod;
        while (n) {
            if (n&1) {
                ans = ans * x % mod;
            }
            x = x * x % mod;
            n >>= 1;
        }
        return ans;
    }

    long long qpow(long long base, long long exp, long long modulo)
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
        return res % modulo;
    }    
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) return -1;
        int m = phi(9 * k); // 9 * k 与 10 互质
        int i = 1;
        for (; i*i<=m; ++i) 
            if (m % i == 0 && pow(10, i, 9*k) == 1) return i;
        
        for (i--; ; i--)
            if (m % i == 0 && pow(10, m / i, k * 9) == 1)
                return m / i;
    }
};