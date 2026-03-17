#include <bits/stdc++.h>
using namespace std;

// 顺序做题
class Solution {
public:
    int minAnagramLength(string s) {
        // 自行解答
        int n = s.length();
        for (int l=1; l<n; l++) {
            if (n % l) continue;
            string first = s.substr(0, l); sort(first.begin(), first.end());

            bool found = true;
            for (int i=l; i<n; i+=l) {
                string other = s.substr(i, l); sort(other.begin(), other.end());
                if (first != other) {
                    found = false; break;
                }
            }

            if (found) return l;
        }
        return n;
    }
}; 