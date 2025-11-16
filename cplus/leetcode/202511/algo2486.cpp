#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.2 判断子序列
class Solution {
public:
    int appendCharacters(string s, string t) {
        // 自行解答
        int inx1 = 0, inx2 = 0, n = s.length(), m = t.length();
        while (inx1 < n && inx2 < m) {
            if (s[inx1] == t[inx2]) inx2 ++;
            inx1 ++;
        }
        return m - inx2;
    }
};