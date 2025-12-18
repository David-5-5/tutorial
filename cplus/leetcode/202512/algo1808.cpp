#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.2 整数拆分
class Solution {
public:
    int maxNiceDivisors(int primeFactors) {
        const int mod = 1e9 + 7;
        if (primeFactors < 5) return primeFactors;
        
        auto qpow = [] (long long x, int e) -> long long {
            long long res = 1;
            while (e) {
                if (e & 1) res = res * x % mod;

                e >>= 1;
                x = x * x % mod;
            }
            return res;
        };

        int expo = primeFactors / 3, rem = primeFactors % 3;
        if (rem == 0) rem = 1;
        else if (rem == 1) expo --, rem += 3;
        return qpow(3, expo) * rem % mod; 
    }
};