#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 1;
bool is_prime[N];
vector<int> primes;
vector<long long> pres = {0};
int init = [] {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false; is_prime[1] = false;
    for (int i = 2; i < N; ++i) {       // 需要统计质数数量，此处不能筛至平方根
        if (is_prime[i]) {
            primes.push_back(i);
            pres.push_back(pres.back() + primes.back());    // 前缀和
            for (long long j = 1LL * i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return 0;
}();


class Solution {
public:
    int largestPrime(int n) {
        if (n == 1) return 0;
        auto it = upper_bound(primes.begin(), primes.end(), n);
        
        while (it!=primes.begin()) {
            auto prime = *prev(it);
            auto it2 = lower_bound(pres.begin(), pres.end(), prime);
            if (*it2 == prime) return prime;
            it --;
        }


        return 0;
    }
};