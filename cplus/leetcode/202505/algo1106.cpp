#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:
    bool parseBoolExpr(string expression) {
        // 自行解答 相比 726 容易多了
        vector<vector<bool>> st(1);
        vector<char> op;

        for (auto& ch : expression) {
            if (ch == '&' || ch == '|' || ch == '!') 
                op.push_back(ch);
            else if (ch == '(') st.emplace_back(); 
            else if (ch == 't') st.back().push_back(true);
            else if (ch == 'f') st.back().push_back(false);
            else if (ch == ')') {
                vector<bool> vals = st.back();
                st.pop_back();
                if (op.back() == '!') st.back().push_back(!vals[0]);
                else if (op.back() == '&') {
                    st.back().push_back(true);
                    for (auto v: vals) st.back().back() = st.back().back() && v;
                } else {
                    st.back().push_back(false);
                    for (auto v: vals) st.back().back() = st.back().back() || v;
                }
                op.pop_back();
            }

        }

        return st[0][0];    
    }
};