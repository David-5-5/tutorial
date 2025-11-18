#include <bits/stdc++.h>
using namespace std;

// 滑动窗口与双指针 - 四、双序列双指针 - 4.2 判断子序列
class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        // 自行解答
        if (str1.length() < str2.length()) return false;
        int inx1 = 0, inx2 = 0, n = str1.length(), m = str2.length();
        while (inx1 < n && inx2 < m) {
            if (str1[inx1] == str2[inx2] ||
                 (str1[inx1]-'a'+1)%26 == str2[inx2]-'a') inx2 ++;
            inx1 ++;
        }
        return m == inx2;           
    }
};