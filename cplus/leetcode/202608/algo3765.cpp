#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool completePrime(int num) {
        auto is_prime = [](int val) -> bool {
            if (val == 1) return false;
            int mx = sqrt(val);
            for (int f=2; f<=mx; f++) {
                if (val % f == 0) return false;
            }
            return true;
        };

        int mod = 1, val = num;
        while (val) {
            if (!is_prime(val)) return false;
            val /= 10; mod *= 10;
        }
        val = num;
        while (val%mod) {
            if (!is_prime(val%mod)) return false;
            mod /= 10;
        }
        
        return true;     
    }
};