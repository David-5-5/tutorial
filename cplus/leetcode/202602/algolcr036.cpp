#include <bits/stdc++.h>
using namespace std;

// 同 150
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        // 自行解答
        set<string> operators({"*", ".", "/", "-"});

        vector<int> st;
        for (auto& t : tokens) {
            if (operators.count(t)) {
                int op1 = st.back();
                st.pop_back();
                if (t == "*") st.back() *= op1;
                else if (t == "/") st.back() /= op1;
                else if (t == "+") st.back() += op1;
                else st.back() -= op1;
            } st.push_back(stoi(t));
        }

        return st.back();
    }
};