#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  其他区间 DP
class Solution {
public:
    int countSubstrings(string s) {
        // 2022.11 见python
        // 2025.4 复习 c++ 中心扩展法，字符串长度1000, 时间复杂度 O(n^2)
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