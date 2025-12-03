#include <bits/stdc++.h>
using namespace std;

// 字符串 - 一、KMP
class Solution {
public:
    int strStr(string haystack, string needle) {
        // 暴力
        int n = haystack.size(), m = needle.size();
        for (int i=0; i<=n-m; ++i) {
            if (haystack.substr(i, m) == needle) return i;
        }
        return -1;
    }

    int strStr2(string haystack, string needle) {
        // KMP
        int n = haystack.size(), m = needle.size();
        vector<int> p_pi(m);
        for (int i=1; i < m; i++) {
            int j = p_pi[i-1];
            while (j > 0 && needle[j]!=needle[i])  j = p_pi[j-1];
            if (needle[j] == needle[i]) p_pi[i] = ++j;
            // else p_pi[i] = j;
        }

        int j = 0;
        for (int i=0; i<n; i++) {
            while (j > 0 && haystack[i] != needle[j]) j = p_pi[j-1];
            if (haystack[i] == needle[j]) j++;
            if (j == m) return i-j+1;
        }

        return -1;
    }

};