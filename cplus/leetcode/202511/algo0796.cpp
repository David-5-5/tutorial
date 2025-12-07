#include <bits/stdc++.h>
using namespace std;

// 字符串 - 一、KMP
class Solution {
public:
    bool rotateString(string s, string goal) {
        return s.length() == goal.length() && (s+s).find(goal) != string::npos;
    }
};