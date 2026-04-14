#include <bits/stdc++.h>
using namespace std;

// 字符串 - 四、字符串哈希
class Solution {
public:
    int distinctEchoSubstrings(string text) {
        // 暴力 - using string-view replace string
        unordered_set<string_view> seen; int n = text.length();
        string_view text_v(text);
        for (int i=0; i<n-1; i++) for (int j=i+1; j<n; j++) {
            if ((j-i+1)%2) continue;
            auto l = (j-i+1) / 2;
            if (!seen.count(text_v.substr(i, 2*l)) && text_v.substr(i, l) == text_v.substr(i+l, l)) 
                seen.insert(text_v.substr(i, 2*l));
        }

        return seen.size(); 
    }
};