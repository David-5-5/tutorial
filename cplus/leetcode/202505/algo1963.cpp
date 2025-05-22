#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    int minSwaps(string s) {
        // 自行解答，栈 + 贪心
        vector<char> st;
        for (auto& ch : s) {
            if (ch == ']' && st.size() && st.back() == '[') st.pop_back();
            else st.push_back(ch);
        }

        return (st.size()/2 + 1) /2; // 剩余类似 ]]]]..][...[[[[, 且数量相等
    }

    int minSwaps2(string s) {
        // 自行解答，计数 + 贪心
        int left = 0, right = 0;
        for (auto& ch : s) {
            if (ch == ']' && left) left--;
            else ch==']'?right++:left++;
        }

        return (right + 1) /2; // 剩余类似 ]]]]..][...[[[[, 且数量相等
    }    
};