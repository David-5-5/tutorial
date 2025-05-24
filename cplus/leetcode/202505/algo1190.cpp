#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    string reverseParentheses(string s) {
        // 自行解答
        vector<char> content;
        vector<int> st;

        for (auto& ch: s) {
            // 记录当前 content 数组的下标位置，后续 char 当前括号内
            if (ch == '(') st.push_back(content.size());
            else if (ch == ')') {
                reverse(content.begin()+st.back(), content.end());
                st.pop_back();
            } else content.push_back(ch);

        }

        string ans = "";
        for (auto& ch : content) ans += ch;
        return ans;
    }
};