#include <bits/stdc++.h>
using namespace std;

// 同 647
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        vector<int> d1(n, 0), d2(n, 0); // d1, d2 s[i] 为中心的奇 偶回文的半径

        // 中心扩展法 类似于 leetcode5 
        for (int i=0; i<n; i++) {
            // 奇回文
            int l = i-1, r = i+1;
            while (l>=0 && r<n && s[l]==s[r]) {
                d1[i] ++;
                l--, r++;
            }
            // 偶回文
            l = i-1, r = i;
            while (l>=0 && r<n && s[l]==s[r]) {
                d2[i] ++;
                l--, r++;
            }
        }

        int ans = 0;
        for (auto& v:d1) ans += 1 + v;
        for (auto& v:d2) ans += v;

        return ans;        
    }
};