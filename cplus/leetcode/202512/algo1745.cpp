#include <bits/stdc++.h>
using namespace std;

// 字符串 - 三、Manacher 算法（回文串）
class Solution {
public:
    bool checkPartitioning(string s) {
        // 暴力 中心扩展法
        int n = s.length();
        auto is_pal = [&](int l, int r) -> bool {
            if (l == r) return true;
            int m1 = (l + r - 1)/2, m2 = (l+r)/2 + 1;
            for (int _=0; _<(r-l+1)/2; _++){
                if (s[m1--] != s[m2++]) return false;
            }
            return true;
        };

        unordered_map<int, bool> memo;
        auto dfs = [&](this auto&& dfs, int st, int left) -> bool {
            if (st == n) return false;
            if (left == 1) return is_pal(st, n-1);
            int mask = st << 2 | left;
            if (memo.count(mask)) return memo[mask];
            for (int j=st; j<n; ++j) {
                if (is_pal(st, j) && dfs(j+1, left-1)) return memo[mask] = true;
            }
            return memo[mask] = false;
        };

        return dfs(0, 3);
    }


    bool checkPartitioning2(string s) {
        // 暴力 中心扩展法 O
        int n = s.length();
        vector is_pal(n, vector<bool>(n, false));
        for (int l=0; l<n; ++l) for (int r=l; r<n; ++r) {
            bool val = true;
            int m1 = (l + r - 1)/2, m2 = (l+r)/2 + 1;
            for (int _=0; _<(r-l+1)/2; _++){
                if (s[m1--] != s[m2++]) {val=false; break;}
            }
            is_pal[l][r] = val;
        };

        for (int l=0; l<n-2; ++l) for (int r=l+2; r<n; ++r) {
            if (is_pal[0][l] && is_pal[l+1][r-1] && is_pal[r][n-1]) return true;
        }
        return false;
    }   

    bool checkPartitioning(string s) {
        // 优化后 中心扩展法
        int n = s.length();

        auto is_pal = [&](int l, int r) -> bool {
            if (l == r) return true;
            int m1 = (l + r - 1)/2, m2 = (l+r)/2 + 1;
            for (int _=0; _<(r-l+1)/2; _++){
                if (s[m1--] != s[m2++]) return false;
            }
            return true;
        };

        vector pre(n, false), suf(n, false);
        for (int r=0; r<n-2; r++)  pre[r] = is_pal(0, r);
        for (int l=2; l<n; l++)  suf[l] = is_pal(l, n-1);
    

        for (int m=1; m<n-1; ++m) {
            int m1 = m, m2 = m + 1;  // 偶数的回文
            while (m1>0 && m2 <n-1) {
                if (s[m1--] == s[m2++]) {
                    if (pre[m1] && suf[m2]) return true;
                } else break;
            }
            m1 = m, m2 = m;         // 奇数回文
            while (m1>0 && m2 <n-1) {
                if (s[m1--] == s[m2++]) {
                    if (pre[m1] && suf[m2]) return true;
                } else break;
            }
        };

        return false;
    }
};