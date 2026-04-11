#include <bits/stdc++.h>
using namespace std;

// 同 343
class Solution {
public:
    int cuttingBamboo(int bamboo_len) {
        int ans = 1;
        for (int k=2; k<=bamboo_len; ++k) {
            int frac = bamboo_len / k, rem = bamboo_len % k;
            int res = 1;
            for (int _=0; _<rem; ++_) res *= (frac+1);
            for (int _=0; _<k-rem; ++_) res *= frac;
            if (res <= ans) break;
            else ans = res;
        }
        return ans;        
    }
};