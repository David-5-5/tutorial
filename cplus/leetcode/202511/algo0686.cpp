#include <bits/stdc++.h>
using namespace std;

// 字符串 - 一、KMP
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        // 参考题解 - 重复字符串 KMP
        auto kmp = [] (string str, string patten) -> int {
            // KMP
            int n = str.size(), m = patten.size();
            vector<int> p_pi(m);
            for (int i=1; i < m; i++) {
                int j = p_pi[i-1];
                while (j > 0 && patten[j]!=patten[i])  j = p_pi[j-1];
                if (patten[j] == patten[i]) p_pi[i] = ++j;
            }

            for (int i=0, j = 0; i-j<n; i++) {
                while (j > 0 && str[i%n] != patten[j]) j = p_pi[j-1];
                if (str[i%n] == patten[j]) j++;
                if (j == m) return i-j+1;
            }

            return -1;
        };
        
        int an = a.size(), bn = b.size();
        int index = kmp(a, b);
        if (index == -1) {
            return -1;
        }
        if (an - index >= bn) {
            return 1;
        }
        return (bn + index - an - 1) / an + 2;
    }
};