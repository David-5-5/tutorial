#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 基础
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        // 自行解答
        stack<int> st;      // 递减队列，index of temperatures
        int n = temperatures.size();
        vector<int> ans(n);

        for (int i=0; i<n; ++i) {
            while (st.size() && temperatures[st.top()]<temperatures[i]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return ans;

    }
};