#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 栈 3.4 合法括号字符串
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        // 自行解答
        int n = seq.length();

        vector<int> ans(n, -1);
        vector<int> st;         // 存储左括号的下标
        for (int i=0; i<n; i++) {
            if (seq[i] == '(') st.push_back(i);
            else {
                int grp = st.size() % 2;    // 按奇偶分组
                ans[i] = grp, ans[st.back()]= grp;
                st.pop_back();
            }
        }
        return ans;
    }
};