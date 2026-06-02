#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.7 分类讨论
class Solution {
public:
    long long smallestNumber(long long num) {
        bool negative = false;
        if (num < 0) negative = true;
        auto abs_n = abs(num); vector<int> cnt(10);

        while (abs_n) {
            cnt[abs_n % 10] ++; abs_n /= 10;
        }
        
        long long ans = 0;
        if (!negative) {
            for (int i=1; i<10; i++) {
                while (cnt[i]) {
                    ans = ans * 10 + i; cnt[i] --;
                    if (cnt[0] && ans) {
                        while (cnt[0]) {ans = ans * 10; cnt[0]--;}
                    }
                }
            }
        } else {
            for (int i=9; i>=0; i--) {
                while (cnt[i]) {
                    ans = ans * 10 + i; cnt[i] --;
                }
            }
        }

        return negative?-ans:ans;     
    }
};