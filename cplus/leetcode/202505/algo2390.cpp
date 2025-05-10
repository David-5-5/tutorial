#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.1 基础
class Solution {
public:
    string removeStars(string s) {
        vector<char> st;

        for (auto ch: s) {
            if (ch == '*') {
                st.pop_back();
            } else {
                st.push_back(ch);
            }
        }

        string ans = "";
        for (auto ch: st) ans += ch;
        return ans;
    }
};