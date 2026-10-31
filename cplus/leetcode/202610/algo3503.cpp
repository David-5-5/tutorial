#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPalindrome(string s, string t) {
        int ans = 1, m = s.length(), n = t.length();
        for (int si=0; si<m; si++) for (int sl=0; sl<=m-si+1; sl++) {
            for (int ti=0; ti<n; ti++) for (int tl=0; tl<=n-ti+1; tl++) {
                auto pal = s.substr(si, sl) + t.substr(ti, tl);
                bool is_pal = true; int len = pal.size();
                for (int i=0; i<len/2; i++) {
                    if (pal[i] != pal[len-i-1]) {
                        is_pal = false; break;
                    }
                }
                if (is_pal) ans = max(ans, len);
            }
        }
        return ans;
    }
};