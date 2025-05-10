#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.1 基础
class Solution {
public:
    string simplifyPath(string path) {
        // 自行解答
        vector<string> st;
        string cur = "";
        path += "/";        // 哨兵

        for (auto& ch: path) {
            if (ch == '/') {
                if (cur == "..") {
                    if (st.size()) st.pop_back();
                } else if (cur.length() && cur != "." )
                    st.push_back(cur);
                cur.clear();
            } else {
                cur += ch;
            }
        }
        string ans = "";
        for (auto& v: st) ans += "/" + v;
        return ans.length()?ans:"/";     
    } 
};