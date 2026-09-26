#include <bits/stdc++.h>
using namespace std;

const int MX = 1001;
vector<int> is_primes(MX, true);
auto init = [] {
    is_primes[0] = false; is_primes[1] = false;
    for (int i=2; i<MX; i++) {
        if (!is_primes[i]) continue;
        for (int j=i*i; j<MX; j+=i) {
            is_primes[j] = false;
        }
    }

    return 0;
}();


class Solution {
private:
    int reverse(int x) {
        int rev = 0;
        while (x) {
            if (rev < INT_MIN/10 || rev > INT_MAX/10) return 0;
            rev = rev * 10 + x % 10;
            x /= 10;
        }

        return rev;
    }    
public:
    int sumOfPrimesInRange(int n) {
        int ans = 0;
        int rev = reverse(n);
        for (int i=min(rev, n); i<=max(rev, n); i++) {
            if (is_primes[i]) ans += i;
        }
        return ans;
    }
};