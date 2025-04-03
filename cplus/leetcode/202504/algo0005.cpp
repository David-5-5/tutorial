#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  其他区间 DP
class Solution {
public:
    string longestPalindrome(string s) {
        // 模板题 中心扩展法
        int len = 1, pos=0, n = s.length();

        for (int i=0; i<n; i++) {
            // 奇回文
            int l = i-1, r = i+1;
            while (l>=0 && r<n && s[l]==s[r]) {
                if (r - l + 1 > len) {
                    len = r - l + 1;
                    pos = l;
                }
                l--, r++;
            }
            // 偶回文
            l = i, r = i+1;
            while (l>=0 && r<n && s[l]==s[r]) {
                if (r - l + 1 > len) {
                    len = r - l + 1;
                    pos = l;
                }
                l--, r++;
            }
        }
        return s.substr(pos, len);  
    }
};