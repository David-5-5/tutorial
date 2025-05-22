#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    bool canBeValid(string s, string locked) {
        // 参考题解
        if (s.length() % 2) return false;

        int n = s.length(), x = 0;
        
        for (int i=0; i<n; ++i) {
            if (s[i] == '(' || locked[i] == '0') x++;
            else if (x)  --x;
            else return false;
        }
        x = 0;
        for (int i=n-1; i>=0; --i) {
            if (s[i] == ')' || locked[i] == '0') x ++;
            else if (x)  --x;
            else return false;
        }

        return true;
    }
};