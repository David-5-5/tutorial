#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    int scoreOfParentheses(string s) {
        // 自行解答
        vector<int> scores;
        vector<int> st;

        for (auto& ch: s) {
            // 记录当前 content 数组的下标位置，后续 char 当前括号内
            if (ch == '(') st.push_back(scores.size());
            else if (ch == ')') {
                if (st.back() == scores.size()) {
                    scores.push_back(1);
                } else {
                    int val = 0;
                    while (scores.size()>st.back()) {
                        val += scores.back();
                        scores.pop_back();
                    }
                    scores.push_back(val * 2);
                }
                st.pop_back();
            }
        }
        int ans = 0;
        for (auto& v: scores) ans += v;
        return ans;
    }
};