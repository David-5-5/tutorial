#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.3 邻项消除
class Solution {
public:
    bool isValid(string s) {
        // 自行解答
        vector<int> st;
        for (auto& ch : s) {
            if (ch != 'c') {
                st.push_back(ch);
            } else {
                if (st.size()>1 && st[st.size()-1] == 'b' && st[st.size()-2] == 'a') {
                    st.pop_back(), st.pop_back();
                } else return false;
            }
        }
        return st.empty();
    }
};