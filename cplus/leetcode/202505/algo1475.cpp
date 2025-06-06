#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 3.7 单调栈 - 基础
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        // 自行解答 非暴力做法 类似于 739
        
        stack<int> st;      // 递增队列，index of temperatures
        int n = prices.size();
        vector<int> ans(n);

        for (int i=0; i<n; ++i) {
            ans[i] = prices[i];
            while (st.size() && prices[st.top()]>=prices[i]) {
                ans[st.top()] -= prices[i];
                st.pop();
            }
            st.push(i);
        }
        return ans;         
    }
};