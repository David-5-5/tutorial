#include <bits/stdc++.h>
using namespace std;

vector<int> bit_cnt(51);
auto init = [] {
    bit_cnt[1] = 2;
    for (int i = 2; i<51; ++i) {
        int pre = i - i/2 - 1;
        bit_cnt[i] = 1 << pre;
    }
    return 0;
}();

// 杂项 - 7.1 回文数
class Solution {
public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1;
        if (n == 1) return 2;

        int ans = 0;
        int w = bit_width((unsigned long long) n);
        
        for (int i=0; i<w; ++i) ans += bit_cnt[i];

        ans += (n >> (w/2)) - (1 << (w-w/2-1));

        int pre = n >> (w - w/2), pre_rev = 0;
        for (int i=0; i<w/2; ++i) {
            pre_rev |= ((pre >> i) & 1) << (w/2-i-1);
        }
        int suffix = n & ((1 << w/2)-1);    // last w/2 bit of n
        if (pre_rev <= suffix) ans ++;
        return ans;
    }
    
};
