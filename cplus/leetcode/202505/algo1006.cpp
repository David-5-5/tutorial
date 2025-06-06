#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.5 表达式解析
class Solution {
public:

    int clumsy(int n) {
        // 参考题解
        stack<int> st;
        st.push(n--);

        int index = 0;
        while (n) {
            if (index % 4 == 0) {
                st.top() *= n;
            } else if (index % 4 == 1) {
                st.top() /= n;
            } else if (index % 4 == 2) {
                st.push(n);
            } else st.push(-n);

            index ++, n--;
        }

        int ans = 0;
        while (!st.empty()) ans += st.top(), st.pop();

        return ans;
    }
};