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

    string largestPalindrome2(int n, int k) {
        // 参考题解，通用方法 DP
        vector<int> pow10(n, 1);
        for (int i=1; i<n; i++) pow10[i] = pow10[i-1] * 10 % k;

        string ans(n, '0');

        int m = (n + 1) >> 1;
        vector vis(m+1, vector<bool>(k));
        auto dfs = [&] (this auto&& dfs, int i, int j) -> bool {
            if (i == m) return  j == 0;
            vis[i][j] = true;
            for (int d=9; d>=0; d--) {
                int j2 = (j + d * pow10[i]) % k;
                if (n-1-i != i) j2 = (j2 + d * pow10[n-1-i]) % k;
                if (!vis[i+1][j2] && dfs(i+1, j2)) {
                    ans[n-i-1] += d; if (n-1-i != i)ans[i] += d; return true;
                }
            }
            return false;

        };

        dfs(0, 0);
        return ans;
    }
}; 