#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 数论 - 1.1 判断质数
class Solution {
public:
    long long sumOfLargestPrimes(string s) {
        set<long long> h_primes;
        auto isprime = [] (long long val) -> bool {
            for (long long i=2; i*i<=val; ++i) {
                if (val % i== 0) return false;
            }
            return val>=2;
        };

        for (int i=0; i<s.length(); ++i) for (int j=1; j<=s.length()-i; ++j) {
            auto val = stol(s.substr(i, j));
            if (isprime(val)) h_primes.insert(val);
        }
        long long ans = 0;
        int offset = max(0, (int)h_primes.size()-3);
        auto it = h_primes.begin();
        if (offset) advance(it, offset);
        for (it; it!=h_primes.end(); ++it) 
            ans += *it;

        return ans;
    }
};