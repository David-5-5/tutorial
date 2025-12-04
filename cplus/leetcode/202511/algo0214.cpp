#include <bits/stdc++.h>
using namespace std;

// 字符串 - 一、KMP
class Solution {
public:
    string shortestPalindrome(string s) {
        // 参考题解 - 求 reverse(s) 和 s 匹配的 pi
        // 要回到前缀函数的定义
        int n = s.size();
        vector<int> p_pi(n);
        for (int i=1; i < n; i++) {
            int j = p_pi[i-1];
            while (j > 0 && s[j]!=s[i])  j = p_pi[j-1];
            if (s[j] == s[i]) p_pi[i] = ++j;
        }

        int j = 0;
        for (int i=n-1; i>=0; i--) {
            while (j > 0 && s[i] != s[j]) j = p_pi[j-1];
            if (s[i] == s[j]) j++;
        }
        string add = (j == n? "" : s.substr(j, n));
        reverse(add.begin(), add.end());
        return add + s;  
    }
};