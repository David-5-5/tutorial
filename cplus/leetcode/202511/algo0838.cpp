#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 六、分组循环
class Solution {
public:
    string pushDominoes(string dominoes) {
        // 参考题解 练习 fill, substr 
        string s = 'L' + dominoes + 'R';
        int n = s.length(), pre = 0;

        for (int i=1; i<n; ++i) {
            if (s[i] == '.') continue;

            if (s[i] == s[pre]) { // L .. L, R..R
                fill(s.begin()+pre+1, s.begin()+i+1, s[i]);
            } else if (s[i] == 'L') {
                fill(s.begin()+pre+1, s.begin()+(i+pre+1)/2, 'R');
                fill(s.begin()+(i+pre)/2+1, s.begin()+i, 'L');
            }
            pre = i;
        }

        return s.substr(1, n-2);
    }
};