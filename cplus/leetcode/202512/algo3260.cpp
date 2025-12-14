#include <bits/stdc++.h>
using namespace std;

// 杂项 - 7.1 回文数
class Solution {
public:
    string largestPalindrome(int n, int k) {
        // 自行解答 分类讨论 找出每个 k 的规律
        string ans(n, '9');
        if (k == 2) {           // 偶数，因此最后必须偶数，最大 8
            ans[0] = '8', ans[n-1] = '8';
        } else if (k == 5) {
            ans[0] = '5', ans[n-1] = '5';            
        } else if (k == 4 || k == 8) {
            // 整除 4 前后最多 4 个 8, 整除 8 前后最多 6 个 8
            // 少于 4, 6 的数量，全为 8
            for (int i=0; i<min((n+1)>>1, bit_width((unsigned)k)-1); ++i) {
                ans[i] = '8', ans[n-1-i] = '8';
            }            
        } else if (k == 6) {    // 偶数，因此最后必须偶数，最大 8，且和为 3 的倍数
            if (n==1) ans[0] = '6';
            else if (n==2) ans = "66";
            else {
                ans[0] = '8', ans[n-1] = '8';
                if (n%2) ans[n/2] = '8';
                else ans[n/2-1] = '7', ans[n/2] = '7';
            }
        } else if (k == 7) {    // 尾数9 可以整除 7, 分奇偶讨论，逐步减少并检查余数是否为 0
            auto check = [&](string val) -> bool{
                int rem = 0;
                for (int i=0; i<n; ++i) rem = (rem * 10 + val[i] - '0') % 7;
                return rem == 0;
            };
            if (n==1) ans[0] = '7';
            else if (n==2) ans = "77";
            else {
                while (!check(ans)) {
                    if (n%2) ans[n/2] --;
                    else ans[n/2-1] --, ans[n/2] --;
                }
            }
        }

        return ans;
    }
};