#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        // 自行解答
        vector<char> content;
        vector<int> st;
        
        for (auto& ch : s) {
            if (ch == '(') {
                st.push_back(content.size());
            } else if (ch == ')') {
                if (st.size()) {
                    content.insert(content.begin()+st.back(), '(');                    
                    content.push_back(')');
                    st.pop_back();
                }
            } else content.push_back(ch);
        }

        string ans;
        for (auto& v : content) ans += v;
        return ans;    
    }
};